#include<iostream>
#include<iomanip>
#include<time.h>
using namespace std;
//!Stores the Linked list node
class node{
	public:
		int data;//!stores the data of node
		node* next;//!pointer to the next node
};
//!A class which defines the operations on the linked list
class LList{

	public: 
		LList()
		{
			head=NULL;
		}    
		void insert(int d); 
		node* head;
		int size;
};
/*!A function that inserts a node at the end of a linked list
  @param d data to be inputted in the linked list*/
void LList::insert(int d)
{
	node* temp=(node*)malloc(sizeof(node));
	temp->data=d;
	temp->next=NULL;
	if(head==NULL)
		head=temp;
	else
	{
		node* current=head;
		while(current->next!=NULL)
			current=current->next;
		current->next=temp;
	}
	size++; 
}
//!A function to print the triplets
//!@param i stores the starting index number
//!@param k stores the ending index number
void print(int i,int k)
{
	for(int a=i+1;a<=k;a++)
		cout<<"("<<i<<","<<a<<","<<k<<")"<<"\n";
}
/*!Consists of an algorithm in which we find the 
  cumulative xor of elements and store it in n
  when this cumulative xor becomes zero we print it...
  */
int main()
{
	clock_t start, end; 
	start = clock(); 
	LList a;//!Stores the elements in a linked list
	LList storei;//!To store the position of i in a linked list
	LList storek;//!To store the position of k in a linked list
	int n;//!number of elements
	int count=0;//!Total number of triplets
	cin >> n;
	int d;
	for(int i=0;i<n;i++)
	{
		cin >> d;
		a.insert(d);
	}
	node* current=a.head;
	for(int i=1;current->next!=NULL;i++)
	{
		int n=current->data;
		node* tmp=current->next;
		for(int j=i+1;tmp!=NULL;j++)
		{
			n=n^tmp->data;
			if(n==0)
			{
				count+=(j-i);
				storei.insert(i);
				storek.insert(j);
			}
			tmp=tmp->next;
		}
		current=current->next;
	}
	cout<<count<<"\n";
	node* temp=storei.head;
	node* temp2=storek.head;
	while(temp!=NULL)
	{print(temp->data,temp2->data);
		temp=temp->next;
		temp2=temp2->next;
	}
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "Time taken by program is : " << fixed  
		<< time_taken << setprecision(5); 
	cout << " sec " << endl; 
	return 0; 
}
