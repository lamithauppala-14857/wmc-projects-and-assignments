# nodes_vs_jitter.py
import matplotlib.pyplot as plt

nodes = [5,10,50,100,150]
jitter = [0.0033,0.00017,0.0757,0.1010,0.1100]

plt.plot(nodes,jitter,marker='o')
plt.xlabel("Nodes")
plt.ylabel("Jitter")
plt.title("Nodes vs Jitter")
plt.grid()
plt.savefig("nodes_vs_jitter.png")
plt.show()