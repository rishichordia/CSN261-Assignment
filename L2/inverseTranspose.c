#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <time.h>	
#include <unistd.h>
int *d;
//!stores the decrypted output 
char decrypted[]="";
//!stores the encrypted input 
char encrypted[]="";

/*! This function reads the encrypted file and stores data in a string
*/
int encrypted_read(int n)
{
        FILE* f =fopen("outputfile.txt","r");
        
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
		  encrypted[x]=ch;
		  x++;
		  }
                fclose(f);
		//printf("%s %d\n",encrypted,x);
		return x;
	}

}
/*!This function is used to decrypt the encrypted output back to its original form using a_prime and b_prime*/
void decrypt(int x,int n,int aa,int b)
{
	char str[x];strcpy(str,encrypted);
	int size=x/n;
	int count=0;
       // for(int i=0;i<15;i++)
        //printf("%c ",encrypted[i]);
	while(count<size)
	{           
              for(int i=0;i<n;i++)
		{
                        int k=(aa*i+b)%n;
                        if(k<0)
				k=k+n;
                        int q=k+count*n;
                        char c=str[q];
			if(c=='\t')
                        decrypted[i+count*n]='\0';
                        else
			decrypted[i+count*n]=c;
                         
                 }
		count++;
	}
        decrypted[x]='\0';
        printf("Sucessfully Decrypted\n");
	printf("%s",decrypted);
      
}



void output()
{
FILE *f=fopen("decryptedOutputfile.txt","w");
if(!f)
printf("error");
else
{fprintf(f,"%s",decrypted);
}
fclose(f);
}




//gives the inverse modulo of a number
int getInversemodulo(int a,int n)
{
 if(a>0)
  {
    for(int i=1;i<n;i++)
       if(a*i%n==1)
        return i;
  }
 else if(a<0)
{
 for(int i=-1;i>a;i--)
  if(a*i%n==1)
    return i;
 }
}



//!Gives  the value of a_prime and b_prime to decrypt the input
int* setDecryptionKey(int n,int a,int b)
{
  d=(int*)malloc(sizeof(int)*3);
  d[0]=n;
  d[1]=getInversemodulo(a,n);
  d[2]=d[1]*b*(-1);
  printf("Encryption Key:\n");
  printf("%d %d %d \n",d[0],d[1],d[2]);
  return d;
}


int main()
{
	double time_spent = 0.0;
	clock_t begin = clock();
     
        int aa[3]={};
        printf("Enter the value of n, a, b:");
        scanf("%d %d %d",&aa[0],&aa[1],&aa[2]);
        int *a=(int*)malloc(sizeof(int)*3);
        a=setDecryptionKey(aa[0],aa[1],aa[2]);
        int c = encrypted_read(aa[0]);
	decrypt(c,a[0],a[1],a[2]);
        output();
        
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);

}
