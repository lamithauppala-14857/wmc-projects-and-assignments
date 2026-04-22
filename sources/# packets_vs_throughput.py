# packets_vs_throughput.py
import matplotlib.pyplot as plt

packets = [100,500,1000,900]
throughput = [16.09,105.55,228.68,102.91]

plt.plot(packets,throughput,marker='o')
plt.xlabel("Packets")
plt.ylabel("Throughput")
plt.title("Packets vs Throughput")
plt.grid()
plt.savefig("packets_vs_throughput.png")
plt.show()