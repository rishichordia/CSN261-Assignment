import networkx as nx
import matplotlib.pyplot as plt
import heapq

H = nx.read_gml('graph .gml',label='label')

def _single_source_dijkstra_path_basic(G,s,weight='weight'):
    # modified from Eppstein
    S=[]
    P={}
    for v in G:
        P[v]=[]
    sigma=dict.fromkeys(G,0.0)    # sigma[v]=0 for v in G
    D={}
    sigma[s]=1.0
    push=heapq.heappush
    pop=heapq.heappop
    seen = {s:0}
    Q=[]   # use Q as heap with (distance,node id) tuples
    push(Q,(0,s,s))
    while Q:
        (dist,pred,v)=pop(Q)
        if v in D:
            continue # already searched this node.
        sigma[v] += sigma[pred] # count paths
        S.append(v)
        D[v] = dist
        for w,edgedata in G[v].items():
            vw_dist = dist + edgedata.get(weight,1)
            if w not in D and (w not in seen or vw_dist < seen[w]):
                seen[w] = vw_dist
                push(Q,(vw_dist,v,w))
                sigma[w]=0.0
                P[w]=[v]
            elif vw_dist==seen[w]:  # handle equal paths
                sigma[w] += sigma[v]
                P[w].append(v)
    return S,P,sigma

def _accumulate_basic(betweenness,S,P,sigma,s):
    delta=dict.fromkeys(S,0)
    while S:
        w=S.pop()
        coeff=(1.0+delta[w])/sigma[w]
        for v in P[w]:
            delta[v] += sigma[v]*coeff
        if w != s:
            betweenness[w]+=delta[w]
    return betweenness

def _rescale_e(betweenness,n,normalized,directed=False):
    if normalized is True:
        if n <=1:
            scale=None  # no normalization b=0 for all nodes
        else:
            scale=1.0/(n*(n-1))
    else: # rescale by 2 for undirected graphs
        if not directed:
            scale=1.0/2.0
        else:
            scale=None
    if scale is not None:
        for v in betweenness:
            betweenness[v] *= scale
    return betweenness

def betweenness_centrality(G, k=None, normalized=True, weight=None, 
                           endpoints=False, seed=None): 
    r"""Compute the shortest-path betweenness centrality for nodes. 
  
    Betweenness centrality of a node $v$ is the sum of the 
    fraction of all-pairs shortest paths that pass through $v$ 
  
    .. math:: 
  
       c_B(v) =\sum_{s,t \in V} \frac{\sigma(s, t|v)}{\sigma(s, t)} 
  
    where $V$ is the set of nodes, $\sigma(s, t)$ is the number of 
    shortest $(s, t)$-paths,  and $\sigma(s, t|v)$ is the number of 
    those paths  passing through some  node $v$ other than $s, t$. 
    If $s = t$, $\sigma(s, t) = 1$, and if $v \in {s, t}$, 
    $\sigma(s, t|v) = 0$ [2]_. 
  
    Parameters 
    ---------- 
    G : graph 
      A NetworkX graph. 
  
    k : int, optional (default=None) 
      If k is not None use k node samples to estimate betweenness. 
      The value of k <= n where n is the number of nodes in the graph. 
      Higher values give better approximation. 
  
    normalized : bool, optional 
      If True the betweenness values are normalized by `2/((n-1)(n-2))` 
      for graphs, and `1/((n-1)(n-2))` for directed graphs where `n` 
      is the number of nodes in G. 
  
    weight : None or string, optional (default=None) 
      If None, all edge weights are considered equal. 
      Otherwise holds the name of the edge attribute used as weight. 
  
    endpoints : bool, optional 
      If True include the endpoints in the shortest path counts. 
  
    Returns 
    ------- 
    nodes : dictionary 
       Dictionary of nodes with betweenness centrality as the value. 
  
      
    Notes 
    ----- 
    The algorithm is from Ulrik Brandes [1]_. 
    See [4]_ for the original first published version and [2]_ for details on 
    algorithms for variations and related metrics. 
  
    For approximate betweenness calculations set k=#samples to use 
    k nodes ("pivots") to estimate the betweenness values. For an estimate 
    of the number of pivots needed see [3]_. 
  
    For weighted graphs the edge weights must be greater than zero. 
    Zero edge weights can produce an infinite number of equal length 
    paths between pairs of nodes. 
  
      
    """
    betweenness = dict.fromkeys(G, 0.0)  # b[v]=0 for v in G 
    nodes = G 
    for s in nodes: 
  
        S, P, sigma = _single_source_dijkstra_path_basic(G, s, weight) 
  
       
        betweenness = _accumulate_basic(betweenness, S, P, sigma, s) 
    
    # rescaling 
    betweenness = _rescale_e(betweenness, len(G), normalized=normalized, directed=G.is_directed()) 
    return betweenness 

# print(betweenness_centrality(H,False,'weight',False,None))
# print(H.edges())
# nx.draw(H)
# for (u,v,d) in H.edges(data='weight'):
#     print('(%s, %s, %.3f)'%(u,v,d))
# nx.draw_random(H)
# nx.draw_circular(H)
# nx.draw_spectral(H)
# plt.show()
# print(nx.betweenness_centrality(H,None,False,'weight'))
print('w:BC(w)')
for key, value in nx.betweenness_centrality(H,None,False,'weight').items():
	print('V{}'.format(key),':', value)
