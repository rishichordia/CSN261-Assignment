# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include<stdbool.h>
//!This structure provides ease of use as it stores the details of a student as a separate entity
typedef struct details
{
	int roll;
	char name[30];
	char dob[10];
	char address[100];
	unsigned long int phone;
}details;
//!This struct defines the student list
typedef struct studentlist
{
	struct studentlist* right;
	struct studentlist* left;
	details data;
}studentlist;
studentlist* head=NULL;//!To define the header node
int size=0, roll_current=101, top=0, queue[13]={0};

/*!this methood is to swap two nodes while sorting as per the requirement of the user
    It uses memmove() function to copy a given memory set to another */
void swap(details *s1, details* s2)
{
      details *t=(details *)malloc(sizeof(details));
      memmove(t,s2,sizeof(details));
      memmove(s2,s1,sizeof(details));
      memmove(s1,t,sizeof(details));
      free(t);     
}

/*	studentlist* t1=s1->left;
        studentlist* t2=s2->right;
	t1->right=s2;
        t2->left=s1;
        s1->left=s2;
        s2->right=s1;
*/
/*!This is a function to insert a node into the doubly circular linked list as per the rool number.
  parameter:details of the student
  It takes into consideration whether any roll no is there in the queue otherwise it assigns a new rol number.
  It implements a simple algorithm to insert with all the cases kept in the mind.*/
void insert(details s)
{
	studentlist* l=(studentlist*)malloc(sizeof(studentlist));
	if(!l)
	{
		printf("\nError");
		return;
	}
	l->data=s;
	if(queue[0]==0)
	{
		l->data.roll=roll_current;
		roll_current++;
	}
	else
	{
		l->data.roll=queue[0];
		for(int i=0; i<top; i++)
			queue[i]=queue[i+1];
		top--;
	}
	if(size==0)
	{
		head=l;
		head->right=head;
		head->left=head;
	}
	else
	{
		studentlist* current=head;
		studentlist* prev=head->left;
		int flag=0,check=1;
		while(current!=head || check)
		{		
			check=0;
			if(l->data.roll<current->data.roll)
			{
				if(current==head)	
					flag=1;
				break;
			}
			current=current->right;
			prev=prev->right;
		}
		prev->right=l;
		current->left=l;
		l->right=current;
		l->left=prev;
		if(flag)
			head=l;
	}
	size++;
}
/*!delete function takes in the roll number of the node to be deleted.
   the deleted roll no gets stored in the queue for further use.
    It also checks for cases where the list is null or the list has only one node*/
void delete(int num)
{
	if(size==0)
	{
		printf("\nStudentlist is empty");
		return;
	}
	else
	{
		studentlist* current=head;
		if(current->data.roll==num && size==1)
		{
			free(current);
			head=NULL;
			size--;
		}
		else
		{
			bool flag_check=true;
			while(current!=head || flag_check)
			{
				flag_check=false;
				if(current->data.roll==num)
				{
					studentlist* temp=current->left;
					studentlist* temp1=current->right;
					temp->right=temp1;
					temp1->left=temp;
					if(current==head)
						head=temp1;
                                        free(current);
					size--;
					queue[top++]=num;
					printf("\nRecord %d deleted ", num);
                                        break;
				}
                                
				current=current->right;
			}
			//printf("\nRecord not found");
                  
		}
	}
}
//!A small function which accepts the data struct object of a student and prints it*/
void print(details data)
{
	printf("\nRoll: %d", data.roll);
	printf("\nName: %s", data.name);
	printf("\nD.O.B: %s", data.dob);
}
//!this method is used to search for a given roll number in the list and print its data
void search(int num)
{
	studentlist* temp=head;
	do
	{
		if(temp->data.roll==num)
			print(temp->data);
	}while(temp->right!=head);
}

/*!This function is used to modify the data of the given roll number
   It searches for the given roll no and then changes the data as per the users requirement*/
void modify(int num)
{
	char str_name[30]="Ritesh Jhunjhunwala";
        char str_address[100]="1600 Pennsylvania Avenue NW in Washington, D.C. ";
	studentlist* temp=head;
	if(head->data.roll==num)
              {
		strcpy(temp->data.name, str_name);
                strcpy(temp->data.address, str_address);
               } 	
	else
	{
		temp=temp->right;
		while(temp!=head)
		{
			if(temp->data.roll==num)
				{strcpy(temp->data.name, str_name);
                                  strcpy(temp->data.address, str_address);
                                }	
			temp=temp->right;
		}
	}
}
/*! simple sorting algo to sort the names of the students alphabetically in ascending order
     It involves the use of strcmp() function of the string header file 
     which is used to compare two functions*/
void bubblesort()
{
        for(int i=0; i<size-1; i++)
	{
		studentlist* temp=head;
		for(int j=0; j<size-i-1; j++)
		{
			studentlist* current=temp;
			temp=temp->right;
                        int c=strcmp(current->data.name,temp->data.name);
                         if(c>0)
				{
                                  swap(&current->data,&temp->data);
		                 }
                 }
	}
}
/*! A function which traverses through the entire doubly linked list 
    untill head node is encountered again and prints the details of the students*/
void printstudentlist()
{
	studentlist* temp=head;
	int i=0;
	if(size==0)
		printf("\nError");
	else
	{
		print(head->data);
		temp=temp->right;
		while(temp!=head)
		{
			print(temp->data);
			temp=temp->right;
		}
	}
}
/*! Note the .xlsx file has been changed to .csv with semicolon as separator to read the data from file
     A function to read data and store it in the respective places in there respective formats
     from a given file given to it 
     with the use of fgets we navigate through the file using THE DELIMITER ';' and using strtok we get the corresponding string  */ 
void read(FILE* f, details records[])
{
	char inp[1000];
	short int count=0;
	fgets(inp,1000,f);
	while(fgets(inp,1000,f))
	{
		char* input_line_values = strtok(inp,";");
		input_line_values = strtok(NULL,";");
		strcpy(records[count].name,input_line_values);
		input_line_values = strtok(NULL,";");
		strcpy(records[count].dob,input_line_values);
		input_line_values = strtok(NULL,";");
		strcpy(records[count].address,input_line_values);
		input_line_values = strtok(NULL,";");
		int num = atoi(input_line_values);
		records[count].phone=num;
		count++;	
	}
}
/*!
    Main function opens the StudentData.csv file in the read mode and the operations mentioned in the question are performed  
*/
int main()
{
	details entry_no[13];
	FILE* file;
	file=fopen("StudentData.csv","r");
	read(file,entry_no);
	delete(108);
	insert(entry_no[0]);
	insert(entry_no[1]);
	insert(entry_no[2]);
	insert(entry_no[3]);
	delete(102);
        delete(101);
	insert(entry_no[4]);
	insert(entry_no[5]);
	insert(entry_no[6]);
        printstudentlist();
        bubblesort();
        printstudentlist();
	modify(103);
	printstudentlist();
	fclose(file);
}

