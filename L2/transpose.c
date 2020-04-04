#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <time.h>	
#include <unistd.h>
int *a;
char filename[100]="";
//!stores the current string
char stri[]="";
//!stores the encrypted version
char encrypted[]="";
//!A function to take and check for correct integral.
int* readinput()
{   
        a=(int*)malloc(3*sizeof(int));        
	char inp[500];fgets(inp,500,stdin);
	char *token = strtok(inp," ");
	if(!token)
	{
		printf("Wrong input");
		exit(0);
	}
	a[0]=atoi(token);
	token=strtok(NULL," ");
	if(!token)
	{
		printf("Wrong input");
		exit(0);
	}

	a[1]=atoi(token);
	token=strtok(NULL," ");
	if(!token)
	{
		printf("Wrong input");
		exit(0);
	}

	a[2]=atoi(token);
	token=strtok(NULL," ");
	if(!token)
	{
		printf("Wrong input");
		exit(0);
	}

	strcpy(filename,token);
	token=strtok(NULL," ");
	if(token)
	{
		printf("Wrong input");
		exit(0);
	}
    return a;
 }
//!A function to read data or text from file
int encrypt_read(int n)
{
        FILE* f =fopen("Sample_testcase_1.txt","r");
        
	if(!f)
	{printf("Cannot open file");
		return 0;
	}
	else
	{
		int x=0;
		  char ch;
		  while((ch=getc(f))!=EOF)
		  {
		  if(ch=='\r')
		  continue;
		  stri[x]=ch;
		  x++;
		  }
                stri[x]='\0';
                while((x%n)!=0)
	        {
		strcat(stri,"\0");
		x++;
	        }
                fclose(f);
		printf("%s \n",stri);
		return x;
	}

}


/*!This function encrypts the output following 
   all the rules of the question*/
void encrypt(int x,int n,int aa,int b)
{
	
        char str[x];strcpy(str,stri);
	int size=x/n;
	int count=0;
        while(count<size)
	{
           for(int i=0;i<n;i++)
		{
                        int k=((aa*i)+b)%n;
                        if(k<0)
			k=k+n;
                        int q=k+count*n;
                       	char c=str[q];
                        if(c=='\0')
                        encrypted[i+count*n]='\t';
                        else
			encrypted[i+count*n]=c;                        
                 }
		count++;
	}
      encrypted[x]='\0';
	printf("Encrypted\n");
   //printf("%s\n",encrypted);      
}

//!A function to display the encrypted output for checking
void output()
{
FILE *f=fopen("outputfile.txt","w");
if(!f)
printf("error");
else
{fprintf(f,"%s",encrypted);
}
fclose(f);
}

int main()
{
        double time_spent = 0.0;
	clock_t begin = clock();
     
        int *b=(int *)malloc(3*sizeof(int));
        b=readinput();
        //printf("%d %d %d ",b[0],b[1],b[2]);
        int c=encrypt_read(b[0]);
        //printf("%d\n",c);
	encrypt(c,b[0],b[1],b[2]);
        //printf("%s\n",encrypted);
        output();
        //printf("%d %d %d ",b[0],b[1],b[2]);
        
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);

}
