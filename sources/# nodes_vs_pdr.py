# nodes_vs_pdr.py
import matplotlib.pyplot as plt

nodes = [5,10,50,100,150]
pdr = [76.92,99.21,80.39,64.31,49.88]

plt.plot(nodes,pdr,marker='o')
plt.xlabel("Nodes")
plt.ylabel("PDR (%)")
plt.title("Nodes vs PDR")
plt.grid()
plt.savefig("nodes_vs_pdr.png")
plt.show()