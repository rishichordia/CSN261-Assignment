import pickle
import networkx as nx
G=nx.read_gpickle('L9_P2_input.gpickle')
node_set=set(G.nodes)
myiter=iter(G.edges)
for n in G.edges:
 print(n.key())
print(G.nodes)
#print(type(myiter))
#print(G.nodes)
#print(G.edges)
class Digraph:
    def __init__(self, nodes,edges):
        self.nodes=set(nodes)
