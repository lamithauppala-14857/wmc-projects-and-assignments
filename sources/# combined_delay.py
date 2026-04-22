# combined_delay.py
import matplotlib.pyplot as plt

x = [1,2,3,4]
nodes_delay = [0.0081,0.00089,0.1698,0.3796]
packets_delay = [0.0081,0.00089,0.3796,0.4604]

plt.plot(x,nodes_delay,label="Nodes Delay")
plt.plot(x,packets_delay,label="Packets Delay")

plt.legend()
plt.title("Combined Delay")
plt.grid()
plt.savefig("combined_delay.png")
plt.show()