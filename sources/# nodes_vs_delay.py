#nodes_vs_delay.py
import matplotlib.pyplot as plt

nodes = [5,10,50,100,150]
delay = [0.0081,0.00089,0.1698,0.3796,0.4604]

plt.plot(nodes,delay,marker='o')
plt.xlabel("Nodes")
plt.ylabel("Delay (sec)")
plt.title("Nodes vs Delay")
plt.grid()
plt.savefig("nodes_vs_delay.png")
plt.show()#