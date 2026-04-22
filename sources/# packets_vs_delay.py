# packets_vs_delay.py
import matplotlib.pyplot as plt

packets = [100,500,1000,900]
delay = [0.0081,0.00089,0.3796,0.4604]

plt.plot(packets,delay,marker='o')
plt.xlabel("Packets")
plt.ylabel("Delay")
plt.title("Packets vs Delay")
plt.grid()
plt.savefig("packets_vs_delay.png")
plt.show()