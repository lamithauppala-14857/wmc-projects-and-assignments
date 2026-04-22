# packets_vs_pdr.py
import matplotlib.pyplot as plt

packets = [100,500,1000,900]
pdr = [76.92,99.21,64.31,49.88]

plt.plot(packets,pdr,marker='o')
plt.xlabel("Packets")
plt.ylabel("PDR (%)")
plt.title("Packets vs PDR")
plt.grid()
plt.savefig("packets_vs_pdr.png")
plt.show()