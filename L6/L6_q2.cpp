#include <iostream>
#include <cstdlib>
#include <fstream>
#include<iomanip>
#include<time.h>
using namespace std;

struct node
{
    int n;
    int degree;
    node* parent;
    node* child;
    node* sibling;
};

ofstream out;
class BinomialHeap
{
    private:
        node *H;
        node *Hr;
        int count;
    public:
        int link_nodes(node*, node*);
        node* create_node(int);
        node* Union_Of_Trees(node*, node*);
        node* insert(node*, node*);
        node* merge_Nodes(node*, node*);
        int display(node*);
        BinomialHeap()
        {
            H =new node();
            H=NULL;
            Hr = new node();
            Hr=NULL;
            int count = 1;
        }
};
int BinomialHeap::link_nodes(node* y, node* z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
    return 0;
}
/*
 * Create Nodes in Binomial Heap
 */
node* BinomialHeap::create_node(int k)
{
    node* p = new node;
    p->n = k;
    return p;
}

node* BinomialHeap::insert(node* H, node* x)
{
    node* H1 = new node();
    H1=NULL;
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union_Of_Trees(H, H1);
    return H;
}
 
node* BinomialHeap::Union_Of_Trees(node* H1, node* H2)
{
    node *H =NULL;
    H = merge_Nodes(H1, H2);
    if (H == NULL)
        return H;
    node* prev_x;
    node* next_x;
    node* x;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
            && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                link_nodes(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                link_nodes(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sibling;
    }
    return H;
}

node* BinomialHeap::merge_Nodes(node* H1, node* H2)
{
    node* H = NULL;
    node* y;
    node* z;
    node* a;
    node* b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}
/*
 * display Binomial Heap
 */
void dis(node*  H)
{
    if (H==NULL)
    {
        return;
    }
    cout<<H->n<<" ";
    dis(H->child);
    if(H->parent!=NULL)
    dis(H->sibling);
    
}
void makeGraph(node* H)
{
    if(H->child==NULL)
    return;
    out<<H->n<<"--"<<H->child->n<<";"<<endl;
    makeGraph(H->child);
    if(H->sibling!=NULL)
    {
        if(H->sibling->parent!=NULL)
        {out<<H->sibling->parent->n<<"--"<<H->sibling->n<<";"<<endl;
        makeGraph(H->sibling);}
    }
}
int BinomialHeap::display(node* H)
{
    if (H == NULL)
    {
        cout<<"The Heap is empty"<<endl;
        return 0;
    }
    node* p;
    p = H;
    while (p != NULL)
    {
        cout<<p->degree<<" : ";
        out<<"subgraph{"<<endl;
        if(p->degree!=0)
        makeGraph(p);
        else
        {
            out<<p->n<<";"<<endl;
        }
        
        dis(p);
        cout<<endl;
        out<<"}"<<endl;
        p = p->sibling;
    }
    cout<<endl;
    return 0;
}

int main()
{
    clock_t start, end; 
	start = clock(); 
    out.open("output.dot");
    out<<"graph{"<<endl;
    int n, m, l, i;
    BinomialHeap bh;
    node* p;
    node *H;
    H = NULL;
    char ch;
    int a;cin>>a;
        for(int i=0;i<a;i++)
        {
            cin>>m;
            p = bh.create_node(m);
            H = bh.insert(H, p);
        }
    
        cout<<"Order: Elements"<<endl;
        bh.display(H);
        out<<"}"<<endl;
    end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "\nTime taken by program is : " << fixed  
		<< time_taken << setprecision(5); 
	cout << " sec " << endl;
	 
    return 0;
}