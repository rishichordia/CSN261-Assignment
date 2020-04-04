import pickle
import networkx as nx
from collections import defaultdict
def dfs_visit(graph, u, status, stack, found_cycle):
    if found_cycle[0]:
        return
    status[u] = "Visited"
    for v in graph[u]:
        if status[v] == "Visited":
            found_cycle[0] = True
            return
        if status[v] == "Not Visited":
            dfs_visit(graph, v, status, stack, found_cycle)
    status[u] = "Finished"     
    stack.append(u)

def topological_sort(graph):          
    stack = []                 
    status = { u : "Not Visited" for u in graph }
    found_cycle = [False]
    for u in graph:
        if status[u] == "Not Visited":
            dfs_visit(graph, u, status, stack, found_cycle)
        if found_cycle[0]:
            break
 
    if found_cycle[0]:            
        stack = []                 
 
    stack.reverse()              
    return stack    


G=nx.read_gpickle('L9_P2_input.gpickle')
node_set=set(G.nodes)
print(G.edges)
graph=dict()
labels=dict()
for node in node_set:
   graph[node]=[]
for edges in G.edges:
    graph[edges[0]].append(edges[1])

#Uncomment this if u wish to sort the adjacency list
"""for node in G.nodes:
   graph[node].sort()"""
#print(graph)
#Test graph
"""graph4 = { 0 : [1, 2],
           1 : [3, 4],
           2 : [],
           3 : [],
           4 : [],
           5 : [7, 6],
           6 : [],
           7 : [] }"""
top_sort=topological_sort(graph)
if(len(top_sort)==0):
    print("The given input is not a DAG")
else:
    print(top_sort)
    #Remove this part if nodes are not integers
    for x in top_sort:
        if(x!=top_sort[-1]):
            print("V"+str(x+1)+",",end=" ")
        else:
            print("V"+str(x+1))
#myiter=iter(node_set)
#for n in G.edges:
#    print(n[0]+n[1])
#print(next(myiter))
