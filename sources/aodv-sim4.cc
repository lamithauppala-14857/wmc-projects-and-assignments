#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/aodv-module.h"
#include "ns3/basic-energy-source-helper.h"
#include "ns3/wifi-radio-energy-model-helper.h"
#include "ns3/netanim-module.h"   // ✅ ADDED

using namespace ns3;

int main(int argc, char *argv[])
{
    uint32_t numNodes = 100;
    uint32_t totalPackets = 1000;
    double simTime = 20.0;

    CommandLine cmd;
    cmd.AddValue("nodes", "Number of nodes", numNodes);
    cmd.AddValue("packets", "Total packets", totalPackets);
    cmd.Parse(argc, argv);

    std::cout << "\n===== USER INPUT =====\n";
    std::cout << "Nodes = " << numNodes << std::endl;
    std::cout << "Packets = " << totalPackets << std::endl;

    NodeContainer nodes;
    nodes.Create(numNodes);

    /* WIFI */
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");

    NetDeviceContainer devices = wifi.Install(phy, mac, nodes);

    /* ✅ MOBILITY FIXED */
    MobilityHelper mobility;

    Ptr<RandomRectanglePositionAllocator> positionAlloc =
    CreateObject<RandomRectanglePositionAllocator>();

    positionAlloc->SetX(CreateObjectWithAttributes<UniformRandomVariable>(
        "Min", DoubleValue(0.0),
        "Max", DoubleValue(100.0)));

    positionAlloc->SetY(CreateObjectWithAttributes<UniformRandomVariable>(
        "Min", DoubleValue(0.0),
        "Max", DoubleValue(100.0)));

    mobility.SetPositionAllocator(positionAlloc);

    mobility.SetMobilityModel(
        "ns3::RandomWaypointMobilityModel",
        "Speed", StringValue("ns3::UniformRandomVariable[Min=5|Max=15]"),
        "Pause", StringValue("ns3::ConstantRandomVariable[Constant=1]"),
        "PositionAllocator", PointerValue(positionAlloc));

    mobility.Install(nodes);

    /* AODV ROUTING */
    AodvHelper aodv;
    InternetStackHelper internet;
    internet.SetRoutingHelper(aodv);
    internet.Install(nodes);

    /* IP */
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0","255.255.255.0");
    Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);

    /* ENERGY */
    BasicEnergySourceHelper energySource;
    energySource.Set("BasicEnergySourceInitialEnergyJ", DoubleValue(20));
    auto sources = energySource.Install(nodes);

    WifiRadioEnergyModelHelper radioEnergy;
    radioEnergy.Install(devices, sources);

    /* TRAFFIC */
    uint16_t port = 9000;

    PacketSinkHelper sink("ns3::UdpSocketFactory",
        Address(InetSocketAddress(Ipv4Address::GetAny(), port)));
    sink.Install(nodes.Get(numNodes - 1));

    UdpClientHelper client(interfaces.GetAddress(numNodes - 1), port);
    client.SetAttribute("MaxPackets", UintegerValue(totalPackets));

    /* ✅ ADAPTIVE LOGIC */
    Ptr<ns3::energy::EnergySource> srcEnergy = sources.Get(0);
    double nodeEnergy = 20;

    if (srcEnergy)
        nodeEnergy = srcEnergy->GetRemainingEnergy();

    Ptr<UniformRandomVariable> randVar = CreateObject<UniformRandomVariable>();
    double interference = randVar->GetValue(0,1);

    double interval;

    if(nodeEnergy < 8)
        interval = 0.05;
    else if(nodeEnergy < 15)
        interval = 0.03;
    else
        interval = 0.01;

    if(interference > 0.7)
        interval += 0.02;

    client.SetAttribute("Interval", TimeValue(Seconds(interval)));
    client.SetAttribute("PacketSize", UintegerValue(512));

    client.Install(nodes.Get(0));

    /* FLOW MONITOR */
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    /* ✅ NETANIM ADDED */
    AnimationInterface anim("aodv-animation.xml");

    // Optional: label nodes (nice visualization)
    for (uint32_t i = 0; i < numNodes; i++)
    {
        anim.UpdateNodeDescription(nodes.Get(i), "Node-" + std::to_string(i));
    }

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    monitor->CheckForLostPackets();
    auto stats = monitor->GetFlowStats();

    uint32_t txPackets = 0, rxPackets = 0, lostPackets = 0;
    double totalDelay = 0, totalJitter = 0;
    double throughput = 0;

    for (auto &flow : stats)
    {
        txPackets += flow.second.txPackets;
        rxPackets += flow.second.rxPackets;
        lostPackets += flow.second.lostPackets;

        totalDelay += flow.second.delaySum.GetSeconds();
        totalJitter += flow.second.jitterSum.GetSeconds();

        throughput += flow.second.rxBytes * 8.0 / simTime / 1024;
    }

    double avgDelay = (rxPackets > 0) ? totalDelay / rxPackets : 0;
    double avgJitter = (rxPackets > 0) ? totalJitter / rxPackets : 0;
    double pdr = (txPackets > 0) ? ((double)rxPackets / txPackets * 100) : 0;

    double communicationOverhead = lostPackets;
    double computationalOverhead = avgDelay * rxPackets;

    double totalEnergyConsumed = 0;
    for (auto i = sources.Begin(); i != sources.End(); ++i)
    {
        totalEnergyConsumed += (20 - (*i)->GetRemainingEnergy());
    }

    double avgEnergy = totalEnergyConsumed / numNodes;

    std::cout << "\n----- Simulation Results -----\n";
    std::cout << "Packets Sent = " << txPackets << std::endl;
    std::cout << "Packets Received = " << rxPackets << std::endl;
    std::cout << "Packet Delivery Ratio (PDR) = " << pdr << " %\n";
    std::cout << "End-to-End Delay = " << avgDelay << " sec\n";
    std::cout << "Average Jitter = " << avgJitter << " sec\n";
    std::cout << "Throughput = " << throughput << " Kbps\n";
    std::cout << "Communication Overhead = " << communicationOverhead << " pkts\n";
    std::cout << "Computational Overhead = " << computationalOverhead << " sec per pkt\n";
    std::cout << "Average Energy Consumption = " << avgEnergy << " Joules\n";

    Simulator::Destroy();
    return 0;
}
