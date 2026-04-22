# combined_pdr.py
import matplotlib.pyplot as plt

x = [1,2,3,4]
nodes_pdr = [76.92,99.21,80.39,64.31]
packets_pdr = [76.92,99.21,64.31,49.88]

plt.plot(x,nodes_pdr,label="Nodes PDR")
plt.plot(x,packets_pdr,label="Packets PDR")

plt.legend()
plt.title("Combined PDR")
plt.grid()
plt.savefig("combined_pdr.png")
plt.show()