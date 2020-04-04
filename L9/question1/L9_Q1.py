import numpy as np
import pickle
import math
from heapq import *
from fibheap import *
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

#def heuristic(a, b):
#    return max(abs(b[0]-a[0]), abs(b[1]-a[1]))
    
def heuristic(a, b):
    return (abs(b[0]-a[0])+ abs(b[1]-a[1]))

def Astar(array, start, goal):

    neighbors = [(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]

    close_set = set()
    came_from = {}
    gscore = {start:0}
    fscore = {start:heuristic(start, goal)}
    fibheap = []

    heappush(fibheap, (fscore[start], start))
    
    while fibheap:

        current = heappop(fibheap)[1]

        if current == goal:
            data = []
            while current in came_from:
                data.append(current)
                current = came_from[current]
            return data

        close_set.add(current)
        for i, j in neighbors:
            neighbor = current[0] + i, current[1] + j            
            tentative_g_score = gscore[current] + heuristic(current, neighbor)
            if 0 <= neighbor[0] < array.shape[0]:
                if 0 <= neighbor[1] < array.shape[1]:                
                    if array[neighbor[0]][neighbor[1]] == 1:
                        continue
                else:
                    continue
            else:
                continue
                
            if neighbor in close_set and tentative_g_score >= gscore.get(neighbor, 0):
                continue
                
            if  tentative_g_score < gscore.get(neighbor, 0) or neighbor not in [i[1]for i in fibheap]:
                came_from[neighbor] = current
                gscore[neighbor] = tentative_g_score
                fscore[neighbor] = tentative_g_score + heuristic(neighbor, goal)
                heappush(fibheap, (fscore[neighbor], neighbor))
                
    return False

nmap = np.array([
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [1,1,1,1,1,1,1,1,1,1,1,1,0,1],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [1,0,1,1,1,1,1,1,1,1,1,1,1,1],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [1,1,1,1,1,1,1,1,1,1,1,1,0,1],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [1,0,1,1,1,1,1,1,1,1,1,1,1,1],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [1,1,1,1,1,1,1,1,1,1,1,1,0,1],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0]])


source = input("Enter source coordinates separated by a space : ")
source = source.split(' ')
source = (int(source[0]),int(source[1]))

destination = input("Enter destination coordinates separated by a space : ")
destination = destination.split(' ')
destination = (int(destination[0]),int(destination[1]))


ipPickleFile = open("L9_P1_input.pkl", "rb")
ipFileData = pickle.load(ipPickleFile)
ipFileData2=ipFileData
nrows = len(ipFileData)
ncols = len(ipFileData[0])
for i in range(nrows):
	for j in range(ncols):
		ipFileData[i][j]=0 if ipFileData[i][j] is 1 else 1
ipPickleFile.close()
nmap1= np.array(ipFileData)
path = Astar(nmap1, source, destination)
print(path)
#print(nmap1)

#discrete_colors = [(255,255,255), (0, 0, 0), (255, 0, 0), (0, 0, 255), (0, 255, 0)]
#my_colormap = colors.ListedColormap(discrete_colors)
colors = [(0,"black"),(0.25,"green"),(0.5,"blue"),(0.75,"red"),(1,"white")]
mycmap = mcolors.LinearSegmentedColormap.from_list("my_colormap", colors)

image = [[1 for i in range(ncols)] for j in range(nrows)]
image[source[0]][source[1]] = 0.25

for row in range(nrows):
    for col in range(ncols):
        if ipFileData[row][col] is 1:
	        image[row][col] = 0
if type(path)!=type(False):
	for (x, y) in path:
    		image[x][y] = 0.5
	image[destination[0]][destination[1]] = 0.75
plt.imshow(image, cmap = mycmap)

ax = plt.gca();

# Major ticks
ax.set_xticks(np.arange(0, nrows, 1));
ax.set_yticks(np.arange(0, ncols, 1));

# Labels for major ticks
ax.set_xticklabels(np.arange(0, nrows, 1));
ax.set_yticklabels(np.arange(0, ncols, 1));

# Minor ticks
ax.set_xticks(np.arange(-0.5, nrows, 1), minor=True);
ax.set_yticks(np.arange(-0.5, ncols, 1), minor=True);

# Gridlines based on minor ticks
ax.grid(which='minor', color='grey', linestyle='-', linewidth=2)
ax.invert_yaxis()
plt.show()
    
