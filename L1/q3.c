#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
int getrow();//!used to find the no of rows in the file
int getcolumn();//!used to find the no of columns in the file
int** readfile(FILE*); 
int** r;//!A dynamic array stores the address of the array that stores the pixel value of red
int** g;//!A dynamic array stores the address of the array that stores the pixel value of green
int** b;//!A dynamic array stores the address of the array that stores the pixel value of blue
int row;//!used to store the no of rows in the file
int col;//!used to store the no of columns in the file
int s;

/*!FUnction to get the pixel value at a given row and column from all the three colour matrices*/
void pixelValue(int x,int y)
{
 printf("Red:%d ",r[x][y]);
 
 printf("Green:%d ",g[x][y]);

 printf("Blue:%d ",b[x][y]);
}


/*!takes the address of the 2d array and displays it on the terminal*/
void displayfile(int **arr)
{
 for(int i=0;i<row;i++)
                    {
                    for(int j=0;j<col;j++)
                      { printf("%d " ,arr[i][j]);}
                     printf("\n");
                    }
                        
       // write_output();
}
/*!A function to remove all the red shades in given image
   A loop traverses through the 2d array and.. 
   It compares the pixel value of the other two by acessing their arrays*/
void removered()
{
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
    if((r[i][j]>g[i][j])&&(r[i][j]>b[i][j]))
       r[i][j]=0;
     }
  } 
}
/*!A function to remove all the green shades in given image
A loop traverses through the 2d array and.. 
   It compares the pixel value of the other two by acessing their arrays*/
void removegreen()
{
    for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
    if((g[i][j]>r[i][j])&&(g[i][j]>b[i][j]))
       g[i][j]=0;
     }
  }

}
/*!A function to remove all the blue shades in given image
A loop traverses through the 2d array and.. 
   It compares the pixel value of the other two by acessing their arrays*/
void removeblue()
{
    for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
    if((b[i][j]>g[i][j])&&(b[i][j]>r[i][j]))
       b[i][j]=0;
     }
  } 
}

/*!It preserves the red colour by removing the green and the blue shades
   first green is removed then blue and again green has to be removed to 
   make sure that no green was remaining after removing blue */
void redOnly()
{
   removegreen();
   removeblue();
   removegreen();
}
/*!It preserves the blue colour by removing the green and the red shades
   first green is removed then red and again green has to be removed to 
   make sure that no green was remaining after removing red */
void blueOnly()
{
  removegreen();
  removered();
   removegreen();
}
/*!It preserves the green colour by removing the red and the blue shades
   first red is removed then blue and again red has to be removed to 
   make sure that no red was remaining after removing blue */

void greenOnly()
{
  removered();
  removeblue();
  removered();
}
/*! Provides a easy interface for the user to use the various functions in the program*/

int main()
{      int get=0;
        row=getrow();
        col=getcolumn();
        s=row*col;
        while(true)
        {FILE *red=fopen("Q3_ip_Red.dat","r");
        FILE *green=fopen("Q3_ip_Green.dat","r");
        FILE *blue=fopen("Q3_ip_Blue.dat","r");
        r=readfile(red);
        g=readfile(green);
        b=readfile(blue);
        printf("Choose an operation\n");
        printf("Enter 1 to remove redshades\n");
        printf("Enter 2 to remove greenshades\n");
        printf("Enter 3 to remove blueshades\n");
        printf("Enter 4 to preserve redshade\n");
        printf("Enter 5 to preserve blueshade\n");
        printf("Enter 6 to preserve greenshade\n");
        printf("Enter 0 to exit\n");
        scanf("%d",&get);
        if(get==0)
         break;
        int x,y;
        switch(get)
        {
        case 0:printf("Exit Thank you");
               break;
        case 1:
                removered();
                printf("The red shade has been removed . To check pixel value enter x<953 and y<1268\n");
                scanf(" %d %d",&x,&y);
                pixelValue(x,y);
                break;
        case 2:
                removegreen();
                printf("The green shade has been removed . To check pixel value enter x<953 and y<1268 \n");
                scanf("%d %d",&x,&y);
                pixelValue(x,y);
                break;
        case 3:
                removeblue();
                printf("The blue shade has been removed . To check pixel value enter x<953 and y<1268\n");
                scanf("%d %d",&x,&y);
                pixelValue(x,y);
                break;
	case 4:
                redOnly();
                printf("The red shade has been preserved . To check pixel value enter x<953 and y<1268\n");
                scanf("%d %d",&x,&y);
                pixelValue(x,y);
                break;
	case 5:
                blueOnly();
                printf("The blue shade has been preserved . To check pixel value enter x<953 and y<1268\n");
                scanf("%d %d",&x,&y);
                pixelValue(x,y);
                break;
	case 6:
                greenOnly();
                printf("The green shade has been preserved . To check pixel value enter x<953 and y<1268\n");
                scanf("%d %d",&x,&y);
                pixelValue(x,y);
                break;
       default: printf("Wrong input selected\n");
       }printf("\n");}
   }
 
/*!
    It reads the given file using its ptr and fscanf
    Generally the delimiter is , but at the end of the line
    the delimiter has been made nextline to avoid any discrepancies 
*/

int** readfile(FILE *f)
   {    
	if(!f)
	{printf("error in opening the file");
         fclose(f);         
        }
	else
	{
		int **arr=(int **)malloc(row*sizeof(int*));
                for (int i= 0; i < row; i++)
                  arr[i]=(int*)malloc(col*sizeof(int*));
                  
                for(int i=0;i<row;i++)
                    {
                    for(int j=0;j<col;j++)
                      { if(j==col-1) 
			fscanf(f,"%d/n" ,&arr[i][j]);
                        else
                         fscanf(f,"%d," ,&arr[i][j]);
	               }
                    }
               fclose(f);
        return(arr);
       }
   }
/*!A function to count the no of rows in the file by basically counting the no of nextline characters 
   using the getc() function*/

int getrow()
{
   int count_lines = 0;
   char chr;
   //extract character from file and store in chr
   FILE *fileptr=fopen("Q3_ip_Red.dat","r");
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
/*!A function to count the no of cols in the file by basically counting the no of characters in a single line 
   using the getc() function and fscanf ,terminating when \n is encountered */
int getcolumn()
{
  FILE *f=fopen("Q3_ip_Red.dat","r");
  if(!f)
	{printf("error in opening the file");
	return -1;}
	else
	{
  int count=1;
  char c;
   c=getc(f);
  do {
   if(c==',')
   count++;
   c=getc(f);
}
   while( c!='\n');
fclose(f);
 return count;
}}

