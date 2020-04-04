#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits.h>
#include <vector>
#include <string>

using namespace std;


class Graph
{
public:
	int adjacency[26][26];
	int vertices;

	Graph()
	{
		for (int i = 0; i < 26; ++i)
		{
			for (int j = 0; i < 26; ++i)
			{
				adjacency[i][j] = 0;
			}
		}
	}

	int getVertices()
	{
		int max = -1;
		for (int i = 0; i < 26; ++i)
		{
			int count = 0;
			for (int j = 0; j < 26; ++j)
			{
				if (adjacency[i][j] > 0)
				{
					count = j+1;
				}
			}

			if (count > max)
			{
				max = count;
			}
		}
		return max;
	}

	void readFromFile(string fileName)
	{
		ifstream file;
		file.open(fileName);
		if (file.is_open())
		{
			string temp;
			while(getline(file,temp))
			{
				char v1,v2,comma;
				int weight;
				stringstream s(temp);
				s >> v1;
				s >> comma;
				s >> v2;
				s >> comma;
				s >> weight;
				this->addEdge(v1,v2,weight);
			}
			file.close();
		}
	}

	void addEdge(char v1, char v2, int weight)
	{
		adjacency[v1%65][v2%65] = weight;
		adjacency[v2%65][v1%65] = weight;
		this->vertices = getVertices();
	}

	void print()
	{
		int vertices = getVertices();
		for (int i = 0; i < vertices; ++i)
		{
			for (int j = i; j < vertices; ++j)
			{
				if (adjacency[i][j] > 0)
				{
					cout << (char)(i+65) << ',' << (char)(j+65) << ',' << adjacency[i][j] << endl;
				}	
			}
		}
	}

};

class HeapNode
{
public:
	HeapNode* parent;
	HeapNode* child;
	HeapNode* left;
	HeapNode* right;
	int key;
	int degree;
	char v1, mark, c;

	HeapNode(char v1,int weight)
	{
		this->v1 = v1;
		this->key = weight;
	}
};


class Heap
{
public:
	HeapNode* minimum;
	int nodes;

	Heap()
	{
		minimum = nullptr;
		nodes = 0;
	}

	void insert(char v1, int weight)
	{
		HeapNode* node = new HeapNode(v1,weight);
		node->degree = 0;
		node->c = 'N';
		node->parent = nullptr;
		node->child = nullptr;
		node->left = node;
		node->right = node;
		if (minimum != nullptr)
		{
			minimum->left->right = node;
			node->right = minimum;
			node->left = minimum->left;
			minimum->left = node;
			if (node->key < minimum->key)
			{
				minimum = node;
			}
		}
		else
		{
			minimum = node;
		}
		nodes++;
	}

	void fibonnaciLink(HeapNode* ptr2, HeapNode* ptr1)
	{
		(ptr2->left)->right = ptr2->right; 
	    (ptr2->right)->left = ptr2->left; 

	    if (ptr1->right == ptr1)
	    { 
	        minimum = ptr1; 
	    }

	    ptr2->left = ptr2; 
	    ptr2->right = ptr2; 
	    ptr2->parent = ptr1;

	    if (ptr1->child == nullptr) 
	    {
	        ptr1->child = ptr2; 
	    }
	    ptr2->right = ptr1->child; 
	    ptr2->left = (ptr1->child)->left; 
	    ((ptr1->child)->left)->right = ptr2; 
	    (ptr1->child)->left = ptr2; 

	    if (ptr2->key < (ptr1->child)->key) 
	    {
	        ptr1->child = ptr2; 
	    }

	    ptr1->degree++;
	}

	void consolidate()
	{
		int temp1;
		int temp2 = (int)(log(nodes)/log(2));

		HeapNode** arr = new HeapNode*[temp2+1];
		for (int i = 0; i <= temp2; ++i)
		{
			arr[i] = nullptr; 
		}

		HeapNode* ptr1 = minimum;
		HeapNode* ptr2;
		HeapNode* ptr3;
		HeapNode* ptr4 = ptr1;

		do
		{
			ptr4 = ptr4->right;
			temp1 = ptr1->degree;
			while(arr[temp1] != nullptr)
			{
				ptr2 = arr[temp1];

				if (ptr1->key > ptr2->key)
				{
					ptr3 = ptr1;
					ptr1 = ptr2;
					ptr2 = ptr3;
				}

				if (ptr2 == minimum)
				{
					minimum = ptr1;
				}

				fibonnaciLink(ptr2, ptr1);

				if (ptr1->right == ptr1)
				{
					minimum = ptr1;
				}
				arr[temp1] = nullptr;
				temp1++;
			}

			arr[temp1] = ptr1;
			ptr1 = ptr1->right;

		}while(ptr1 != minimum);

		minimum = nullptr;

		for (int j = 0; j <= temp2; ++j)
		{
			if (arr[j] != nullptr)
			{ 

	            arr[j]->left = arr[j]; 
	            arr[j]->right = arr[j]; 

	            if (minimum != nullptr)
	            { 
	                (minimum->left)->right = arr[j]; 
	                arr[j]->right = minimum; 
	                arr[j]->left = minimum->left; 
	                minimum->left = arr[j]; 
	                if (arr[j]->key < minimum->key) 
	                {
	                    minimum = arr[j]; 
	                }
	            } 
	            else
	            { 
	                minimum = arr[j]; 
	            } 
	            if (minimum == nullptr) 
	            {
	                minimum = arr[j]; 
	            }
	            else if(arr[j]->key < minimum->key) 
	            {
	                minimum = arr[j]; 
	            }
        	}
		}

	}

	HeapNode* extractMin()
	{
		HeapNode* retVal = minimum;
		if (minimum != nullptr)
		{
			HeapNode* temp = minimum; 
	        HeapNode* pntr; 
	        pntr = temp; 
	        HeapNode* x = nullptr; 
	        if (temp->child != nullptr) { 
	  
	            x = temp->child; 
	            do
	            { 
	                pntr = x->right; 
	                (minimum->left)->right = x; 
	                x->right = minimum; 
	                x->left = minimum->left; 
	                minimum->left = x; 
	                if (x->key < minimum->key)
	               	{ 
	                    minimum = x; 
	                }
	                x->parent = nullptr; 
	                x = pntr; 
	            } while (pntr != temp->child); 
	        } 

	        (temp->left)->right = temp->right; 
	        (temp->right)->left = temp->left; 
	        minimum = temp->right; 

	        if (temp == temp->right && temp->child == nullptr) 
	        {
	            minimum = nullptr; 
	        }
	        else
	        { 
	            minimum = temp->right; 
	            consolidate(); 
	        } 
	        nodes--; 
		}

		return retVal;


	}

	void cut(HeapNode* found, HeapNode* temp) 
	{ 
	    if (found == found->right)
	    { 
	        temp->child = nullptr; 
	    }
	  
	    (found->left)->right = found->right; 
	    (found->right)->left = found->left; 

	    if (found == temp->child) 
	    {
	        temp->child = found->right; 
	    }
	  
	    temp->degree = temp->degree - 1; 
	    found->right = found; 
	    found->left = found; 
	    (minimum->left)->right = found; 
	    found->right = minimum; 
	    found->left = minimum->left; 
	    minimum->left = found; 
	    found->parent = nullptr; 
	    found->mark = 'B'; 
	}

	void cascadeCut(HeapNode* temp) 
	{ 
	    HeapNode* ptr5 = temp->parent; 
	    if (ptr5 != nullptr)
	    { 
	        if (temp->mark == 'W')
	        { 
	            temp->mark = 'B'; 
	        } 
	        else
	        { 
	            cut(temp, ptr5); 
	            cascadeCut(ptr5); 
	        } 
	    } 
	}

	void decreaseKey(HeapNode* found, int val) 
	{ 
	    found->key = val; 
	  
	    HeapNode* temp = found->parent; 
	    if (temp != nullptr && found->key < temp->key)
	    { 
	        cut(found, temp); 
	        cascadeCut(temp); 
	    } 
	    if (found->key < minimum->key)
	    {
	        minimum = found; 
	    }
	}

	HeapNode* find(HeapNode* minimum, char v) 
	{ 
		HeapNode* toReturn;
	    HeapNode* found = nullptr; 
	    HeapNode* temp5 = minimum; 
	    temp5->c = 'Y'; 
	    HeapNode* found_ptr = nullptr;

	    if (temp5->v1 == v)
	    { 
	        found_ptr = temp5; 
	        temp5->c = 'N'; 
	        found = found_ptr; 
	        toReturn = found; 
	    } 
	    if (found_ptr == nullptr)
	    { 
	        if (temp5->child != nullptr)
	       	{ 
	            toReturn = find(temp5->child, v);
	        } 
	        if ((temp5->right)->c != 'Y')
	        {
	            toReturn = find(temp5->right, v); 
	        }
	    } 
	    temp5->c = 'N'; 
	    found = found_ptr; 

	    return toReturn;
	}


};


void newwick(vector<string>** wick,Graph* mst, char* parent,char v)
{
	for (int i=0; i < mst->vertices; ++i)
	{
		if ((char)(parent[i]+65) == v)
		{
			newwick(wick,mst,parent,(char)(i+65));
			string s = "";
			if (!wick[i]->empty())
			{
				s += "(";
				for (auto it = wick[i]->begin(); it != wick[i]->end(); ++it)
				{
					s += *it;
					if (*it != wick[i]->back())
					{
						s+= ",";
					}
				}
				s+= ")";
			}
			s+= (char)(i+65);
			s+= ':';
			s+= to_string(mst->adjacency[i][v%65]);

			wick[v%65]->push_back(s);
		}
	}
}



int main(void)
{
	Graph* graph = new Graph();
	graph->readFromFile("2019_CSN_261_L5_P2.csv");

	Heap* fibonacciHeap = new Heap();

	bool* mstSet = new bool[graph->vertices];
	char* parent = new char[graph->vertices];
	for (int i = 0; i < graph->vertices; ++i)
	{
		mstSet[i] = false;
		parent[i] = -1;
	}

	fibonacciHeap->insert((char)65,0);

	for (int i = 1; i < graph->vertices; ++i)
	{
		fibonacciHeap->insert((char)(i+65),INT_MAX);
	}

	for (int i = 0; i < graph->vertices - 1; ++i)
	{
		HeapNode* min = fibonacciHeap->extractMin();
		mstSet[min->v1 % 65] = true;

		for (int i = 0; i < graph->vertices; ++i)
		{
			HeapNode* node = fibonacciHeap->find(fibonacciHeap->minimum,i+65);
			if (node != nullptr && graph->adjacency[min->v1 % 65][i] != 0 && mstSet[i] == false && graph->adjacency[min->v1 % 65][i] < node->key )
			{
				parent[i] = min->v1 % 65;
				fibonacciHeap->decreaseKey(node,graph->adjacency[min->v1 % 65][i]);
			}
		}
	}

	Graph* mst = new Graph();
	int tot_weight = 0;
	for (int i = 0; i < graph->vertices; ++i)
	{
		int curr_weight = graph->adjacency[i][parent[i]];
		tot_weight += curr_weight;
		mst->addEdge((char)(parent[i]+65), (char)(i+65), curr_weight);
	}

	mst->print();
	cout << endl;
	cout << "The total edge weight of the MST is : " << tot_weight << endl;

	vector<string>** wick = new vector<string>*[mst->vertices];
	for (int i = 0; i < mst->vertices; ++i)
	{
		wick[i] = new vector<string>();
	}

	newwick(wick,mst,parent,'A');
	string s = "";
	if (!wick[0]->empty())
	{
		s += "(";
		for (auto it = wick[0]->begin(); it != wick[0]->end(); ++it)
		{
			s += *it;
			if (*it != wick[0]->back())
			{
				s+= ",";
			}
		}
		s+= ")";
	}
	s+="A;";

	ofstream file;
	file.open("prim.nw");
	if (file.is_open())
	{
		file << s << endl;
		file.close();
	}

	return 0;
}