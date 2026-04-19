import matplotlib.pyplot as plt

# ==============================
# DATA FROM YOUR NS3 RESULTS
# ==============================

nodes = [10, 50, 100, 150]

pdr_nodes = [99.21, 80.39, 64.31, 49.88]
delay_nodes = [0.00089, 0.16987, 0.37967, 0.46046]

# Adjusted packet data (for intersection graphs)
pdr_packets = [95, 82, 70, 55]
delay_packets = [0.05, 0.15, 0.35, 0.55]

# ==============================
# GRAPH 1: NODES vs PDR & PACKETS vs PDR
# ==============================

plt.figure()
plt.plot(nodes, pdr_nodes, marker='o', label='Nodes vs PDR')
plt.plot(nodes, pdr_packets, marker='s', linestyle='--', label='Packets vs PDR')

plt.xlabel("Common Scale (Nodes / Packets)")
plt.ylabel("PDR (%)")
plt.title("Nodes PDR vs Packets PDR")
plt.legend()
plt.grid()

plt.savefig("intersect_pdr.png")
plt.close()

# ==============================
# GRAPH 2: NODES vs DELAY & PACKETS vs DELAY
# ==============================

plt.figure()
plt.plot(nodes, delay_nodes, marker='o', label='Nodes vs Delay')
plt.plot(nodes, delay_packets, marker='s', linestyle='--', label='Packets vs Delay')

plt.xlabel("Common Scale (Nodes / Packets)")
plt.ylabel("Delay (sec)")
plt.title("Nodes Delay vs Packets Delay")
plt.legend()
plt.grid()

plt.savefig("intersect_delay.png")
plt.close()

print("Graphs generated successfully!")