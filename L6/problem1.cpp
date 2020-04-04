#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int val;
	Node* next;
	Node(int a)
	{
		val=a;
		next=NULL;
	}
};
Node* adjacency[100];
int min_dist[100][100];
bool visited[100];
Node* store_res;
int source;
bool is_cycle;
void insert(int a,int b)
{
	Node* x=adjacency[a];
	if(x==NULL)
		adjacency[a]=new Node(b);
	else
	{
		while(x->next!=NULL)
			x=x->next;
		x->next=new Node(b);
	}
	return;
}
void insert_result(int a)
{
	Node* x=store_res;
	if(x==NULL)
		store_res=new Node(a);
	else
	{
		while(x->next!=NULL)
			x=x->next;
		x->next=new Node(a);
	}
	return;
}
void dfs(int v,int p)
{
	visited[v]=true;
	insert_result(v);
	Node* x=adjacency[v];
	while(x!=NULL)
	{
		if(!visited[x->val])
			dfs(x->val,v);
		else if(x->val!=p)
			is_cycle=true;
		x=x->next;
	}
	return;
}
int main()
{
	char v1,v2;
	string line;
	int ch;
	source=-1;
	fstream fp;
	fp.open("L6_Q1_sample_input.txt");
	if(!fp.is_open())
		cout<<"Unable to open input file."<<endl;
	do
	{
		cout<<"1 - Insert Edges"<<endl;
		cout<<"2 - BFS traversal"<<endl;
		cout<<"3 - DFS traversal"<<endl;
		cout<<"4 - Cycle finding in the graph"<<endl;
		cout<<"5 - Calculate diameter of the graph"<<endl;
		cout<<"6 - Exit"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:
			while(getline(fp,line))
			{
				v1=line[0];
				v2=line[2];
				insert((int)v1-(int)'A',(int)v2-(int)'A');
				insert((int)v2-(int)'A',(int)v1-(int)'A');
				if(source==-1)
					source=(int)v1-(int)'A';
			}
			break;
			case 2:
			{
				if(source==-1)
					break;
				store_res=NULL;
				memset(visited,false,sizeof(visited));
				insert_result(source);
				visited[source]=true;
				while(store_res!=NULL)
				{
					int v=store_res->val;
					cout<<(char)(v+(int)'A')<<" ";	
					Node* x=adjacency[v];
					while(x!=NULL)
					{
						if(!visited[x->val])
						{
							insert_result(x->val);
							visited[x->val]=true;
						}
						x=x->next;
					}
					store_res=store_res->next;
				}
				cout<<endl;
				break;
			}
			case 3:
			{
				if(source==-1)
					break;
				store_res=NULL;
				memset(visited,false,sizeof(visited));
				dfs(source,-1);
				Node* x=store_res;
				while(x!=NULL)
				{
					cout<<(char)(x->val+(int)'A')<<" ";
					x=x->next;
				}
				cout<<endl;
				break;
			}
			case 4:
			{
				if(source==-1)
					break;
				store_res=NULL;
				memset(visited,false,sizeof(visited));
				is_cycle=false;
				dfs(source,-1);
				if(is_cycle)
					cout<<"Yes"<<endl;
				else
					cout<<"No"<<endl;
				break;
			}
			case 5:
			{
				if(source==-1)
					break;
				for(int i=0;i<100;i++)
					for(int j=0;j<100;j++)
						min_dist[i][j]=1000;
				for(int i=0;i<100;i++)
				{
					Node* x=adjacency[i];
					while(x!=NULL)
					{
						min_dist[i][x->val]=1;
						min_dist[x->val][i]=1;
						x=x->next;
					}
					min_dist[i][i]=0;	
				}
				for(int i=0;i<100;i++)
					for(int j=0;j<100;j++)
						for(int k=0;k<100;k++)
							if(min_dist[j][i]+min_dist[i][k]<min_dist[j][k])
								min_dist[j][k]=min_dist[j][i]+min_dist[i][k];
				int diameter=0;
				for(int i=0;i<100;i++)
					for(int j=0;j<100;j++)
						if(min_dist[i][j]!=1000 && min_dist[i][j]>diameter)
							diameter=min_dist[i][j];
				cout<<"Diameter: "<<diameter<<endl;
				break;
			}
			default:
			break;
		}
	}
	while(ch!=6);
	fp.close();
	return 0;
}