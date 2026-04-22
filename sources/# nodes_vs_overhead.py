# nodes_vs_overhead.py
import matplotlib.pyplot as plt

nodes = [5,10,50,100,150]
overhead = [24,4,120,510,2936]

plt.plot(nodes,overhead,marker='o')
plt.xlabel("Nodes")
plt.ylabel("Overhead")
plt.title("Nodes vs Overhead")
plt.grid()
plt.savefig("nodes_vs_overhead.png")
plt.show()