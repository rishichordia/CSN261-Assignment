#include<stdio.h>
#include<stdlib.h>

int front=-1;   //!defines first node index of the circular deque
int rear=-1;    //!defines last node index of the circular deque
int size=1;     //!defines size the circular deque
void insertfront(int *deque,int value);
void insertback(int *deque,int value);
void deleteback(int *deque);
void deletefront(int *deque);
/*! This is the basic function used to print the contents,sizeand no of elements in the deque*/
void print_deque(int *deque)
{
	if(rear!=-1)
	{
		

	printf("\nThe size of the queue is %d\n",size);
	printf("The no of elements in it is %d \n",(rear+1));

	}
	else
	printf("Empty queue");
}
/*!It implements all the possible cases with the deque 
   It  involves the implementation of all the four functions of deque*/
int main()
{

	int* deque=(int*)malloc(sizeof(int));
	insertfront(deque,5);
	insertfront(deque,6);
        insertfront(deque,7);
        insertfront(deque,8);
        insertfront(deque,9);        
        print_deque(deque);
        deletefront(deque);
        deleteback(deque);	
	print_deque(deque);
	
	/*print_deque(deque);
        
	print_deque(deque);
        deletefront(deque);
	print_deque(deque);*/
}
/*! It inserts the value at the front end of the deque 
    It is programmed so as to double the size of the deque when size is full */
	void insertfront(int *deque,int value)
	{
		if(size==1&&rear==-1)
		{
			rear=0;
			front=0;
			deque[0]=value;
		}
		else
		{
			if(rear==size-1)
			{
				size*=2;
				deque=(int*)realloc(deque,size*sizeof(int));
						}
						for(int i=0;i<=rear;i++)
						{
						deque[i+1]=deque[i];
						}
						deque[0]=value;
						rear++;
						}
						}
/*! It inserts the value at the back end of the deque 
    It is programmed so as to double the size of the deque when size is full */

	void insertback(int *deque,int value)
	{
	if(size==1)
	{
	rear=0;
	front=0;
	deque[0]=value;
	}
	else
	{
	if(rear==size-1)
	{
		size*=2;
		deque=(int*)realloc(deque,size*sizeof(int));
				}
				rear++;
				deque[rear]=value;
				}
				}

/*! It deletes the value at the back end of the deque 
    It is programmed so as to half the size of the deque when no of elements are less than half */

	void deleteback(int *deque)
	{
	if(size==1&&rear==0)
	{
	rear=-1;
	front=-1;
	deque[0]=0;
	}
	else if(rear!=-1)
	{
	if((rear)*2<=size)
	{
		size=size/2;
		deque=(int*)realloc(deque,size*sizeof(int));
	}
				rear--;
	}
	}

/*! It deletes the value at the front end of the deque 
    It is programmed so as to half the size of the deque when no of elements are less than half */
	void deletefront(int *deque)
	{
	if(size==1&&rear==0)
	{
	rear=-1;
	front=-1;
	deque[0]=0;
	}
	else if(rear!=-1)
	{
	for(int i=0;i<rear;i++)
	{
		deque[i]=deque[i+1];
	}
	rear--;
	if((rear+1)*2<=size)
	{
		size=size/2;
		deque=(int*)realloc(deque,size*sizeof(int));
				}
				}
				}



