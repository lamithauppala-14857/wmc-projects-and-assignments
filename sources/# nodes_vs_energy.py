# nodes_vs_energy.py
import matplotlib.pyplot as plt

nodes = [5,10,50,100,150]
energy = [14.39,14.41,14.54,14.84,15.04]

plt.plot(nodes,energy,marker='o')
plt.xlabel("Nodes")
plt.ylabel("Energy (J)")
plt.title("Nodes vs Energy")
plt.grid()
plt.savefig("nodes_vs_energy.png")
plt.show()