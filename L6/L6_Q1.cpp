#include<iostream>
#include<fstream>
#include<iomanip>
#include<time.h>
using namespace std;
const int N = 26;

int edges = 0;
int vertices;


class stack
{
public:
    char arr [N];
    int top;
    stack() { top = 0;}
    void push(char x){arr[top] = x;
    top++;}
    void pop(){top--;}
	void reset(){top = 0;}
	bool find(char x)
	{
		for(int i = 0;i<top;i++)
		if(x == arr[i]) return true;
		return false;
	}
	void print()
	{
	cout<<endl;
	for(int i=0;i<top;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
	}
};

class Graph{
private:
	char key;
	Graph* List[N];
	int degree;
public:
	Graph()
	{
	for(int i=0;i<N;i++)
		List[i] = NULL;
	degree = 0;
	key = 0;
	}
	void setKey(char x)
	{
		key = x;
	}
	void operator+(Graph& Node2)
	{
	this->List[degree] = &Node2;
	Node2.List[Node2.degree] = this;
	this->degree++;
	Node2.degree++;
	}
	int longestPath();
	void printBFS();
	void printDFS()
	{
	stack buffer;
	auxDFS(*this,buffer);
	buffer.print();
	vertices = buffer.top;
	}
	
friend void auxDFS(Graph& current,stack& buffer);
};

void auxDFS(Graph& current,stack& buffer)
{
	if(buffer.find(current.key)) return;
	buffer.push(current.key);
	for(int i = 0;i<current.degree;i++)
	{
		auxDFS(*current.List[i],buffer);
	}
}

class queue{
public:
	Graph* arr[N];
	int back;
	queue()
	{
		for(int i=0;i<N;i++)
			arr[i] = NULL;
	       	back =0;
	}
	void push(Graph* inp)
	{
		arr[back] = inp;
		back++;
	}
	void pop()
	{
		Graph* temp;
		for(int i = 0;i<back;i++)
		{
			temp = arr[i];
			arr[i] = arr[i+1];
			arr[i+1] = temp;
		}
		back--;
	}
};
int Graph::longestPath()
{
	int dist[N];
	for(int i = 0;i<N;i++)dist[i] = 0;
	int max = 0;
	queue buffer;
	buffer.push(this);
	stack bufferPrint;
	bufferPrint.push(this->key);
	while(buffer.back>0)
	{
		for(int i =0;i<buffer.arr[0]->degree;i++)
		if(!(bufferPrint.find(buffer.arr[0]->List[i]->key)))
		{
			bufferPrint.push(buffer.arr[0]->List[i]->key);
			buffer.push((buffer.arr[0]->List[i]));
			dist[int(buffer.arr[0]->List[i]->key)-65]= dist[int(buffer.arr[0]->key)-65] + 1;
		}
		buffer.pop();
	}
	for(int i = 0;i<N;i++)	if(dist[i]>max) max = dist[i];
	return max;
}


void Graph::printBFS()
{
	queue buffer;
	buffer.push(this);
	stack bufferPrint;
	bufferPrint.push(this->key);
	while(buffer.back>0)
	{
		for(int i =0;i<buffer.arr[0]->degree;i++)
		if(!(bufferPrint.find(buffer.arr[0]->List[i]->key)))
		{
			bufferPrint.push(buffer.arr[0]->List[i]->key);
			buffer.push((buffer.arr[0]->List[i]));
		}
		buffer.pop();
	}
	bufferPrint.print();
	
}
int main()
{
	clock_t start, end;
	ifstream input;
	input.open("L6_Q1_sample_input.txt");
	char temp,temp1;

	Graph array[N];
	for(int i=0;i<N;i++) array[i].setKey(char(i+65));
	

	int max = 0;

	while(input>>temp)
	{
		edges ++;
		input>>temp1;
		array[int(temp)-65] + array[int(temp1) -65];
	}

	input.clear();
	input.seekg(0,ios::beg);
	double time_taken;
	char x,y;
	int choice=0;//!<User choice
        while(choice != 6)
        {
                cout<<"\n\n -----------MENU----------------\n\n";
                cout<<"\n1. To insert an edge";
                cout<<"\n2. BFS traversal";
                cout<<"\n3. DFS traversal";
                cout<<"\n4. To check if cycle present (connected graph)";
                cout<<"\n5. Diameter of the graph";
                cout<<"\n6. Exit\n\n";
                cout<<"Your choice: ";
                 cin>>choice;

                 switch(choice)
                 {
                         case 1:
                                start = clock(); 
								cout<<"\nEnter input vertex IDs (uppercase): ";
				cin>>x>>y;
				array[int(x-65)] + array [int(y-65)];
				end = clock();
				 time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
				cout << "\nTime taken by program is : " << fixed  << time_taken << setprecision(5); 
				cout << " sec " << endl;
                                break;
                         case 2:
						 start = clock(); 
				cout<<"Enter the root node for BFS traversal:";
				cin>>x;
				array[int(x-65)].printBFS();
				end = clock();
				time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "\nTime taken by program is : " << fixed  << time_taken << setprecision(5); 
	cout << " sec " << endl;
                                break;
                         case 3:
						 start = clock(); 
				cout<<"Enter the root node for DFS traversal:";
				cin>>x;
				array[int(x-65)].printDFS();
				end = clock();
				 time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "\nTime taken by program is : " << fixed  << time_taken << setprecision(5); 
	cout << " sec " << endl;
                                break;
                         case 4:
						 start = clock(); 
				array[0].printDFS();
				if(vertices == edges) cout<<"\nFalse";
				else cout<<"\nTrue";
				end = clock();
				 time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "\nTime taken by program is : " << fixed  << time_taken << setprecision(5); 
	cout << " sec " << endl;
                                break;
                         case 5:
						 start = clock(); 
				while(input>>temp)
				{
					if (max < (array[temp-65].longestPath())) max = array[temp-65].longestPath();
				}
				cout<<"\nThe diameter is "<<max<<endl;
				end = clock();
				 time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "\nTime taken by program is : " << fixed  << time_taken << setprecision(5); 
	cout << " sec " << endl;
                                break;
                         case 6:
                                return 0;
                         default:
                                cout<<"\nInvalid choice";
                 }
        }
	input.close();	 
}
