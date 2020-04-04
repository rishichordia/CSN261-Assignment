#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include<time.h>
using namespace std;
//!It will store the inorder traversal of BST to form AVL
int *arr;
//!A node that describes individuals of a tree
class node{
	public:
		int data;//!stores the value
		char color;//!stores the value
		node* left;
		node* right;
		node* parent;
		//!Constructor
		node()
		{
			left=NULL;
			right=NULL;
			color='r';
			parent=NULL;
		}
};
//!Defines the operations on Binary search Tree
class BST
{
	public: 
		//!Constructor
		BST()
		{
			root=NULL;
		}    
		void insert(int d); 
		void giveInorderArray(node* root);
		node* root;
		int size;//!number of nodes of the tree
};
//!Defines the operations on Binary search Tree

class RedBlack {
	public:
		int size;//!number of nodes of the tree
		node* rootRB;
		RedBlack()
		{
			rootRB=NULL;
		}
		void insertRB(int d);
		void managePosition(node *&ptr,node*& root);
		void rotateRight(node *&root, node *&ptr);
		void rotateLeft(node *&root, node *&ptr);
};

/*!A function to insert a node in rb tree normally without balancing and recolouring
  @param d Stores the data t be inserted*/
void RedBlack::insertRB(int d)
{
	node* temp=new node;
	temp->data=d;
	size++;
	if(rootRB==NULL)
	{rootRB=temp;
		rootRB->color='b';
	}
	else
	{
		node* current=rootRB;
		node* tmp=NULL;
		int c;
		while(current!=NULL)
		{
			tmp=current;
			c=current->data;
			if(d>=c)
				current=current->right;

			else if(d<c)
				current=current->left;
		}
		if(d<tmp->data)
		{tmp->left=temp;
		}
		else if(d>=tmp->data)
			tmp->right=temp;
		temp->parent=tmp;
		managePosition(temp,rootRB);
	}

}
/*!A function that performs the left rotations as necessary on the RB Tree
  @param root Stores the data root node of the RB tree
  @param ptr Stores the current node pointer which has to be rotated
  */void RedBlack::rotateLeft(node *&root, node *&ptr) 
{ 
	node *pt_right = ptr->right; 

	ptr->right = pt_right->left; 

	if (ptr->right != NULL) 
		ptr->right->parent = ptr; 

	pt_right->parent = ptr->parent; 

	if (ptr->parent == NULL) 
		root = pt_right; 

	else if (ptr == ptr->parent->left) 
		ptr->parent->left = pt_right; 

	else
		ptr->parent->right = pt_right; 

	pt_right->left = ptr; 
	ptr->parent = pt_right; 
} 
/*!A function that performs the right rotations as necessary on the RB Tree
  @param root Stores the data root node of the RB tree
  @param ptr Stores the current node pointer which has to be rotated
  */
void RedBlack::rotateRight(node *&root, node *&ptr) 
{ 
	node *pt_left = ptr->left; 

	ptr->left = pt_left->right; 

	if (ptr->left != NULL) 
		ptr->left->parent = ptr; 

	pt_left->parent = ptr->parent; 

	if (ptr->parent == NULL) 
		root = pt_left; 

	else if (ptr == ptr->parent->left) 
		ptr->parent->left = pt_left; 

	else
		ptr->parent->right = pt_left; 

	pt_left->right = ptr; 
	ptr->parent = pt_left; 
} 
/*!The most important function of the red black tree
  which handles any discrapancies in the tree
  It takes the root node and the current node as parameters
  It checks for the uncle node to be red or black and performs the operations accordingly
  @param root Stores the data root node of the RB tree
  @param ptr Stores the current node pointer which has to be rotated
  */
void RedBlack::managePosition(node *&ptr,node *&root)
{
	node* p=NULL;//!parent of the current node
	node* gp=NULL;//!GrandParent of the current node
	while((ptr!=root)&&(ptr->parent->color!='b')&&(ptr->color!='b'))
	{	p=ptr->parent;
		gp=ptr->parent->parent;
		node* uncle=new node();
		if(p==gp->left)
		{	uncle=gp->right;

			if(uncle!=NULL&&uncle->color=='r')
			{
				uncle->color='b';
				p->color='b';
				gp->color='r';
				ptr=gp;
			}
			else
			{
				if (ptr== p->right) 
				{ 
					rotateLeft(root,p); 
					ptr=p; 
					p = ptr->parent; 
				} 
				rotateRight(root, gp);
				char c=p->color;
				p->color= gp->color;
				gp->color=c; 
				ptr=p; 
			}
		}
		else if(p==gp->right)
		{
			uncle=gp->left;
			if(uncle!=NULL&&uncle->color=='r')
			{
				uncle->color='b';
				p->color='b';
				gp->color='b';
				ptr=gp;
			}
			else
			{
				if (ptr== p->left) 
				{ 
					rotateRight(root, p); 
					ptr = p; 
					p = ptr->parent; 
				}
				rotateLeft(root, gp); 
				char c=p->color;
				p->color= gp->color;
				gp->color=c; 
				ptr=p; 
			}
		}

	}
	root->color='b';
}
/*!A function to insert into the BST Tree using basic methods
  @param d Stores the data to be inserted into the tree
  */void BST::insert(int d)
{
	node* temp=new node;
	temp->data=d;

	if(root==NULL)
		root=temp;
	else
	{
		node* current=root;
		node* tmp=NULL;
		int c;
		while(current!=NULL)
		{
			tmp=current;
			c=current->data;
			if(d>=c)
				current=current->right;

			else if(d<c)
				current=current->left;
		}
		if(d<tmp->data)
			tmp->left=temp;
		else if(d>=tmp->data)
			tmp->right=temp;
	}
	size++; 
}
int i=0;
/*!A function to give the inorder array from the given root node
  @param root Stores the data root node of the given tree whose inorder is to be stored */
void BST::giveInorderArray(node* root)
{
	if(!root)
		return;
	giveInorderArray(root->left);
	arr[i++]=root->data;
	giveInorderArray(root->right);
}
/*!A more general function that prints the inorder of any of the trees depending on the root node
  @param root Stores the data root node of the given tree whose inorder is to be printed*/
void printInorder(node* root)
{
	if(!root)
		return;
	printInorder(root->left);
	cout<<root->data<<" ";
	printInorder(root->right);

}
//!Calculates the height of given root using basic recursive algorithms
//!@param root Stores the data root node of the given tree whose height is to be calculated
int height(node* root)
{
	if(!root)
		return 0;
	int r=height(root->left);
	int l=height(root->right);
	if(r>l)
		return r+1;
	return l+1;
}
//!Rotates the avl branch towards right
//!@param y Stores the current pointer
node *rightRotate(node *y)  
{  
	node *x = y->left;  
	node *temp = x->right; 
	x->right = y;  
	y->left = temp;  
	return x;  
}
//!Rotates the avl branch towards left
//!@param x Stores the current pointer
node *leftRotate(node *x)  
{  
	node *y = x->right;  
	node *temp = y->left;
	y->left = x;  
	x->right = temp;
	return y;  
}  
//!A function inserts an element in avl tree and performs the relevant balancijng operations
//!@param ptr is the current node pointer....
//!@param num is the data to be inserted in the avl tree while creating it 
node* insertAVL(node* ptr, int num)  
{  
	if (ptr == NULL)
	{ptr=new node();
		ptr->data=num; 
		return(ptr); }

	if (num < ptr->data)  
		ptr->left = insertAVL(ptr->left, num);  
	else if (num > ptr->data)  
		ptr->right = insertAVL(ptr->right, num);  
	else  
		return ptr;  
	int balance = height(ptr->right)-height(ptr->left);  

	if (balance <-1 && num < ptr->left->data)  
		return rightRotate(ptr);

	if (balance >1 && num > ptr->right->data)  
		return leftRotate(ptr);  

	if (balance < -1 && num > ptr->left->data)  
	{  
		ptr->left = leftRotate(ptr->left);  
		return rightRotate(ptr);  
	}  
	if (balance > 1 && num < ptr->right->data)  
	{  
		ptr->right = rightRotate(ptr->right);  
		return leftRotate(ptr);  
	}  
	return ptr;  
}  
//!A very general function that prints the Tree with level wise indentation
//!@param head Stores the root node of the given tree which is to be printed
//!@param spaces stores the number of spaces from the margin to be displayed to provide proper indentation
//!@param rbt counter true only for red black tree
void print(node* head,int spaces,bool rbt)
{
	if(head==NULL)
		return;
	int n=height(head->right)-height(head->left);
	for(int i=0;i<=spaces;i++)
		cout<<" ";
	if(head->right==NULL&&head->left==NULL)
		cout<<head->data;
	else
		cout<<head->data<<"["<<n<<"]"; 
	if(rbt)
	{
		if(head->color=='r')
			cout<<" [RED]";
		else if(head->color=='b')
			cout<<" [BLACK]";
	}

	cout<<endl; 
	spaces+=8;  
	print(head->left,spaces,rbt);
	print(head->right,spaces,rbt);
}

//!Stack are needed while displaying the paths as we use the Depth First Search Algorithm
class Stack { 
	int top; 

	public: 
	int a[20];

	Stack() { top = -1; }
	//!Pushes x into the stack 
	void push(int x)
	{ 
		if (top >= (20 - 1)) { 
			cout << "Stack Overflow"; 
		} 
		else { 
			a[++top] = x;  
		} 
	} 
	//!pops from the stack 
	void pop()
	{ 
		if (top < 0) { 
			cout << "Stack Underflow"; 
		} 
		else { 
			int x = a[top--]; 
		} 
	}  
	//!Prints the elements in the required form
	void printFromStack()
	{
		for(int i=0;i<=top;i++)
		{
			for(int j=i;j<=top;j++)
			{if(j!=top)
				cout<<a[j]<<"->";
				else
					cout<<a[j];
			}
			cout<<"\n";
		}
	} 
}s;
//!An function that searches for leaf node and prints all the possible paths using stacks
//!Here s is the stack object
//!@param head Stores the root node of the given tree whose paths are to be printedvoid searchLeaf(node* head)
void searchLeaf(node* head)
{
	int c=head->data;
	if(head->right==NULL&&head->left==NULL)
	{
		s.push(c);
		s.printFromStack();
		s.pop();
		return;
	}
	s.push(c);
	if(head->left!=NULL)
		searchLeaf(head->left);
	if(head->right!=NULL)
		searchLeaf(head->right);
	s.pop();
}
/*!
  The driving function of the entire program...
  It consists of a menu driven User interface that is elegant to use with and free of bugs and discrepancies
  as all the cases are taken into consideration
  @param argc to define the number of input being taken from the terminal
  @param arcv to store the inputs from the terminal
  */
int main(int argc,char* argv[])
{
	clock_t start, end; 
	start = clock();
	//!the Binary Search Tree object
	BST *a=new BST();
	//!The AVL Tree object
	BST *avl=new BST();
	//!The red Black Tree object
	RedBlack *b=new RedBlack();
	int n,d;
	for(int i=2;i<=argc;i++)
	{
		d=atoi(argv[i-1]);
		a->insert(d);
		b->insertRB(d);
	}
	bool avl_created=false;//!Checks if AVL tree created
	do
	{
		cout<<"\nList of operations that can be performed\n";
		cout<<"Enter 1 : To insert a node in the BST and in the red-black tree\n";
		cout<<"Enter 2 : To create AVL tree from the inorder traversal of the BST\n";
		cout<<"Enter 3 : To print the inorder traversal of the BST/AVL/red-black tree\n";
		cout<<"Enter 4 : To display all the paths in the BST/AVL tree/red-black tree\n";
		cout<<"Enter 5 : To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation\n";
		cout<<"Enter 6 : Exit \n\n";
inp: cin>>n;
     int y;
     switch (n){
	     case 1:
		     {cout<<"Enter the value to be inserted\n";
			     int x;
			     cin>>x;
			     a->insert(x);
			     b->insertRB(x);
			     cout<<"Sucessfully inserted\n\n";
			     goto inp;
		     }
		     break;
	     case 2:
		     {arr=(int*)malloc(a->size*sizeof(int));
			     avl->size=a->size;
			     avl_created=true;
			     a->giveInorderArray(a->root);
			     for(int i=0;i<a->size;i++)
				     avl->root=insertAVL(avl->root,arr[i]);
			     cout<<"AVL Tree sucessfuly created\n\n";
			     free(arr);
			     i=0;
			     goto inp;
		     }
		     break;
	     case 3:
		     {cout<<"\nEnter 1 for BST\nEnter 2 for AVL Tree\nEnter 3 for Red-Black Tree\nEnter 4 to go back to the main menu\n";
a: cin>>y;
   if(y==1)
   {cout<<"Inorder Traversal(This output is for BST Tree):\n";
	   printInorder(a->root);
	   cout<<endl;}
   else if(y==2&&avl_created)
   {cout<<"Inorder Traversal(This output is for AVL Tree):\n";
	   printInorder(avl->root);cout<<endl;}
   else if(y==3)
   {cout<<"Inorder Traversal(This output is for Red Black Tree):\n";
	   printInorder(b->rootRB);cout<<endl;}
   else if(y!=4&&avl_created)
	   cout<<"Wrong Input\n";
   if(y!=4)
	   goto a;
		     }
		     break;
	     case 4:
		     {cout<<"\nEnter 1 for paths of BST\nEnter 2 for paths of AVL Tree\nEnter 3 for paths of Red-Black Tree\nEnter 4 to go back to the main menu\n";
b: cin>>y;cout<<endl;
   if(y==1)
	   searchLeaf(a->root);
   else if(y==2&&avl_created)
	   searchLeaf(avl->root);
   else if(y==3)
	   searchLeaf(b->rootRB);
   else if(y!=4&&avl_created)
	   cout<<"Wrong Input\n";
   if(y!=4)
	   goto b;
		     }
		     break;
	     case 5:
		     {cout<<"\nEnter 1 to print BST\nEnter 2 to print AVL Tree\nEnter 3 to print Red-Black Tree\nEnter 4 to go back to the main menu\n";
c: cin>>y;cout<<"";
   if(y==1)
	   print(a->root,1,false);
   else if(y==2&&avl_created)
	   print(avl->root,1,false);
   else if(y==3)
	   print(b->rootRB,1,true);
   else if(y!=4&&avl_created)
	   cout<<"Wrong Input\n";
   if(y!=4)
	   goto c;
		     }
		     break;
	     case 6:
		     break;
	     default:{cout<<"\nWrong choice\n";}
     }
	}
	while(n!=6);
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "Time taken by program is : " << fixed  
		<< time_taken << setprecision(5); 
	cout << " sec " << endl; 
	return 0; 	
}