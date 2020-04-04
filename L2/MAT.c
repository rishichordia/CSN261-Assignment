#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <time.h>	
#include <unistd.h>
typedef struct Tree_node node;
//!Input Array Pointer
int **a;
//!Output Array Pointer
int **out;
int s;
int get_n();
int** readfile(FILE *f,int n,int c);
void generate( node* root,int x,int y,int size);
/*! Defines the tree node's Structure
    The most important feature is that it should have degree 4 representing the four directions 
    in which we can move in the array
*/
struct Tree_node{
	int num;int dig;int size;
	node* nw;
	node* ne;
	node* sw;
	node* se;
};
node* root=NULL;

//!A function that creates a leaf node and separately identifies it as a leaf node by assigning it a num
node* create_leaf( int size,int x,int y,int co)
{
        node* temp = ( node *)malloc(sizeof( node));
	temp->dig= a[x][y];
	temp->size= size;
	int d=0;
	for(int i=size;i<=s;i*=2)d++;
	printf("(%d, %d, %d)\n",co,temp->dig,d-1); 
	temp->num=co;
	temp->nw = NULL;
	temp->ne = NULL;
	temp->sw = NULL; 
	temp->se = NULL;
	return temp; 
}

//!A function that creates a non-leaf node and separately identifies it by assigning it's size to zero
node* create_node()
{
	node* temp = ( node *)malloc(sizeof( node));
	temp->size =0;
	temp->dig =-1;
	temp->nw = NULL;
	temp->ne = NULL;
	temp->sw = NULL; 
	temp->se = NULL;
	return temp;
}


/*!This function checks whether a given region of the array has all values same or not
   using the current position int the array along with the size*/
bool check_array(int x,int y,int size)
{
	int q=a[x][y];
        int lx=x+size-1;
        int ly=y+size-1;
	for(int i=x;i<=lx;i++)
		for(int j=y;j<=ly;j++)
			if(a[i][j]!=q)
				return false;
	return true;
}


//!This function Updates a given region of the output array using the values that are required in the question
void update_matrix(int size,int x,int y,int co)
{
        int lx=x+size-1;
        int ly=y+size-1;
	for(int i=x;i<=lx;i++)
		for(int j=y;j<=ly;j++)
			out[i][j]=co;
}


/*!The most important function which generates the tree from a given input array
   using the current position.We keep dividing the array into blocks of four and call the function recursively*/
void generate( node* root,int x,int y,int size)
{
       static int count=0;       
       if(size==1)
	{
	        count++;
		root=create_leaf(size,x,y,count);
		update_matrix(size,x,y,count);
		return;
	}
	if(check_array(x,y,size))
	{
	        count++;
	        root=create_leaf(size,x,y,count);
	        update_matrix(size,x,y,count);
		return;
	} 
	root->nw=create_node();
	root->ne=create_node();
	root->sw=create_node();
	root->se=create_node();
	generate(root->nw,x,y,size/2);

	generate(root->ne,x,(y+size/2),size/2);

	generate(root->sw,(x+size/2),y,size/2);

	generate(root->se,x+ size/2,y + size/2,size/2);

}

/*!It displays the output in a post order manner*/

void out_tree(node* current)
{
 static int depth=0;
 if(!current)
   {depth--;
   return;}
   depth++;
   out_tree(current->nw);
   depth++;
   out_tree(current->ne);
   depth++;
   out_tree(current->sw);
   depth++;
   out_tree(current->se);
   if(current->size!=0)
      printf("(%d, %d, %d)",current->num,current->dig,depth);
}

/*!The  function that controls the execution of the entire program*/

int main()
{
       double time_spent = 0.0;
	clock_t begin = clock();
     

        FILE *f=fopen("inputSample.txt","r");
	int n = get_n();
	int c =n;
        int i;
        for(i=1;i<c;i*=2);
        for(;c<i;c++);
         s=c;  
        printf("%d\n",n); 
	printf("%d\n",c);
	a=readfile(f,n,c);
	out=(int **)calloc(c,sizeof(int*));
	for (int i= 0; i < c; i++)
	    out[i]=(int*)calloc(c,sizeof(int*));
			       
	root = ( node *)malloc(sizeof( node));
	root->nw = NULL;
  	root->ne = NULL;
  	root->sw = NULL; 
  	root->se = NULL;
  	root->size=0;
  	node *head=(node *)malloc(sizeof( node));
  	head=root;
  	generate(root,0,0,c);
  	out_tree(head);
        for(int i=0;i<c;i++)
	{
		for(int j=0;j<c;j++)
			printf("%d  ",out[i][j]);
	 printf("\n");
        }
        
        
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);

	return 0;
      
}

/*!Reads data from the file and stores a matrix at the 
   south west corner if its size is not a power of two
 */
int** readfile(FILE *f,int  n,int c)
{    
	if(!f)
	{printf("error in opening the file");
		fclose(f);         
	}
	else
	{
		int **arr=(int **)calloc(c,sizeof(int*));
		for (int i= 0; i < c; i++)
			arr[i]=(int*)calloc(c,sizeof(int*));

		for(int i=0;i<c;i++)
		{
			for(int j=0;j<c;j++)
				if(j==n-1 && i>=c-n && j>=c-n) 
					fscanf(f,"%d/n" ,&arr[i][j]);
				else if (i>=c-n&&j>=c-n)
					fscanf(f,"%d " ,&arr[i][j]);   
		}

		fclose(f);
		return(arr);
	}
}
/*!A function to count the no of rows in the file by basically counting the no of nextline characters 
  using the getc() function*/

int get_n()
{
	int count_lines = 0;
	char chr;
	//extract character from file and store in chr
	FILE *fileptr=fopen("inputSample.txt","r");
	if(!fileptr)
	{printf("error in opening the file");
		return -1;
	}
	else
	{    
		chr = getc(fileptr);
		while (chr != EOF)
		{
			//Count whenever new line is encountered
			if (chr == '\n')
			{
				count_lines = count_lines + 1;
			}
			//take next character from file.
			chr = getc(fileptr);
		}
		fclose(fileptr); //close file.
	}
	return count_lines;
}

