# nodes_vs_throughput.py
import matplotlib.pyplot as plt

nodes = [5,10,50,100,150]
throughput = [16.09,105.55,152.28,228.68,102.91]

plt.plot(nodes,throughput,marker='o')
plt.xlabel("Nodes")
plt.ylabel("Throughput (Kbps)")
plt.title("Nodes vs Throughput")
plt.grid()
plt.savefig("nodes_vs_throughput.png")
plt.show()