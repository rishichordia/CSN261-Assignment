#include<iostream> 
#include<vector>
#include<algorithm>
#include<string.h>
#include<fstream>
using namespace std; 

vector<char> verticeSet1;
vector<char> verticeSet2;
vector<int> wts;
vector<char> vertices;
int check = 0;
int check1 = 0;
int check2 = 0;

class Graph{
public: 
	int nVerts, nEdges; 
	vector< pair<int, pair<int, int>> > edges; 
 
	Graph(int nVerts, int nEdges) 
	{ 
		this->nVerts = nVerts; 
		this->nEdges = nEdges; 
	} 

	void addEdge(int vert1, int vert2, int weight) 
	{ 
		edges.push_back({weight, {vert1, vert2}}); 
	} 
 
	int makeMST(); 
}; 
 
class DisjointSets{
public: 
	int *parent, *rank; 
	int n; 

	DisjointSets(int n) { 
		this->n = n; 
		parent = new int[n+1]; 
		rank = new int[n+1]; 

		for (int i = 0; i <= n; i++) 
		{ 
			rank[i] = 0; 

			parent[i] = i; 
		} 
	} 

	int find(int v) { 
		if (v != parent[v]) 
			parent[v] = find(parent[v]); 
		return parent[v]; 
	} 

	void merge(int v1, int v2) { 
		v1 = find(v1);
		v2 = find(v2); 

		if (rank[v1] > rank[v2]) {
			parent[v2] = v1; 
		}else{
			parent[v1] = v2;
		}
		
		if (rank[v1] == rank[v2]) {
			rank[v2]++; 
		}
	} 	
}; 

int Graph::makeMST(){ 
	int MSTweight = 0;

	sort(edges.begin(), edges.end()); 

	DisjointSets djSets(nVerts);

	cout << "graph MST { " << endl;

	vector< pair<int, pair<int, int>> >::iterator it; 
	for (it=edges.begin(); it!=edges.end(); it++) 
	{ 
		int u = it->second.first; 
		int v = it->second.second; 

		int set_u = djSets.find(u); 
		int set_v = djSets.find(v); 

		if (set_u != set_v) 
		{ 
			int i = 0;

			for(i = 0; i < verticeSet1.size(); i++){
				if(((int)verticeSet1[i]-65)==u){
					if(((int)verticeSet2[i]-65)==v){
						break;
					}
				}
			}

			cout << "\t" << (char)(u+65) << " -- " << (char)(v+65) << " [label=" << wts[i] << "];" <<endl; 

			MSTweight += it->first; 

			djSets.merge(set_u, set_v); 
		} 
	}

	cout << "}\n"; 

	return MSTweight; 
} 

Graph *undirecGraph;

void getData(char* fileName){
	char ipChar;
	ifstream inputFile;
	inputFile.open(fileName);
	while(inputFile >> ipChar){
		if(ipChar != ','){
			if(check == 2){
				if((65<=(int)ipChar)&&((int)ipChar<=90)){
					check = 0;
				}else if(wts.size() < verticeSet1.size()){
					wts.push_back(int(ipChar)-48);
				}else{
					wts[wts.size() -1] = 10*wts[wts.size() -1] + int(ipChar)-48;
				}
			}
			if(check == 0){
				check2 = 0;
				for(int j =  0; j < vertices.size(); j++){
					if(ipChar == vertices[j]){
						check2 = 1;
					}
				}
				verticeSet1.push_back(ipChar);
				if(check2 == 0){
					vertices.push_back(ipChar);
				}
			}else if(check == 1){
				check2 = 0;
				for(int j =  0; j < vertices.size(); j++){
					if(ipChar == vertices[j]){
						check2 = 1;
					}
				}
				verticeSet2.push_back(ipChar);
				if(check2 == 0){
					vertices.push_back(ipChar);
				}
			}
		}else{
			check +=1;
		}
	}
}

void createGraph(){
	int nVerts = vertices.size();
	int nEdges = wts.size();

	undirecGraph = new Graph(nVerts, nEdges);

	for(int i = 0; i < verticeSet1.size(); i++){
		undirecGraph->addEdge(((int)verticeSet1[i]-65), ((int)verticeSet2[i]-65), wts[i]);
	}
}

int main() 
{ 
	string file = "2019_CSN_261_L5_P2.csv";
	int n = file.length(); 
    char array[n + 1]; 
    strcpy(array, file.c_str());
	
	getData(array);
	createGraph();

	int MSTweight = undirecGraph->makeMST(); 

	return 0; 
} 
