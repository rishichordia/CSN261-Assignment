#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <time.h>	
#include <unistd.h>
char stri[]="";
char decrypted[]="";

//!reads from original input file and stores in stri
char* original_read()
{
        FILE* f =fopen("Sample_testcase_1.txt","r");
        printf("Input:\n");
	if(!f)
	{printf("Cannot open file");
	}
	else
	{
		int x=0;
		  char ch;
		  while((ch=getc(f))!=EOF)
		  {
		  stri[x]=ch;
		  x++;
		  }
                stri[x]='\0';
                fclose(f);
	}
    return stri;
}

//!reads from decryptedOutputfile file and stores in decrypted
char* decrypted_read()
{	printf("Decrypted Output:\n");
        FILE* f =fopen("decryptedOutputfile.txt","r");
        
	if(!f)
	printf("Cannot open file");
	else
	{
		int x=0;
		  char ch;
		  while((ch=getc(f))!=EOF)
		  {
		  decrypted[x]=ch;
		  x++;
		  }
		  decrypted[x]='\0';
                fclose(f);
	}
      return decrypted;
}

int main()
{
	double time_spent = 0.0;
	clock_t begin = clock();
     
        char *s1=original_read();
        printf("%s \n",stri);
        char *s2=decrypted_read();
	printf("%s",decrypted);
	
	clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);

}
