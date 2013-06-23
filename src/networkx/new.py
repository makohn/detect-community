import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
edge_file = open('3980.edges', 'r')
cmty_file = open('3980.cmtys', 'r')
color = ['r', 'b', 'g']
edges = [data.strip().split() for data in edge_file]
cmtys = [data.strip().split() for data in cmty_file]
edge_file.close()
cmty_file.close()

G.add_edges_from(edges)
nodes = G.nodes()
G.add_edges_from([(0, i) for i in nodes])

pos = nx.spring_layout(G)
for i in range(3):
    nx.draw_networkx(G, pos = pos, nodelist = cmtys[i], node_color = color[i])
    plt.xlim(-0.05,1.05)
    plt.ylim(-0.05,1.05)
    plt.axis('off')
    plt.show()
