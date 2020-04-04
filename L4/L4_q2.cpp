#include<iostream>
#include<iomanip>
#include<time.h>
using namespace std;
int n;//!Stores the number N of the N-Queens problem
int **board;//!Basically stores the N*N Board
//!A function to print the current orientation of the board after checking
void printSolution() 
{ 
    static int k = 1; 
    cout<<"Combination :"<<k++<<"\n"; 
    for (int i = 0; i < n; i++) 
    { 
        for (int j = 0; j < n; j++)
            cout<< board[i][j]<<" "; 
        cout<<endl;
    } 
    cout<<endl; 
}
//!A function to check if the given orientation of the Board Satisfies the conditions of the N Queens Problem or not
//!@param row represents the current row
//!@param col represents the current column
bool checkOrientation( int row, int col) 
{ 
    int i, j; 

    for (i = 0; i < col; i++) 
        if (board[row][i]) 
            return false; 
 
    for (i=row, j=col; i>=0 && j>=0; i--, j--) 
        if (board[i][j]) 
            return false; 
  
    for (i=row, j=col; j>=0 && i<n; i++, j--) 
        if (board[i][j]) 
            return false; 
  
    return true; 
} 
//!The main Driving Function that uses recursion to according to the backTracing Technique to Solve the problem
//!@param col Since we are doing it columnwise so we are taking the current column as the input
bool solve( int col) 
{ 
   
    if (col == n) 
    { 
        printSolution(); 
        return true; 
    } 
  
    bool result = false; 
    for (int i = 0; i < n; i++) 
    { 
        if ( checkOrientation( i, col) ) 
        { 
            
            board[i][col] = 1; 
            result = solve( col + 1) || result; 
            board[i][col] = 0; 
        } 
    } 
      return result; 
} 
//!A function that checks whether a solution exists or not
void solveNQueens()
{ 

    if (solve(0) == false) 
    { 
        cout<<"Solution does not exist"; 
        return ; 
    } 
  
    return ; 
} 
//!The driver function that takes the n as input and runs the function. It also calculates the time of processing
int main() 
{ 
	clock_t start, end; 
	start = clock(); 
	
    cin>>n;
    cout<<endl;
   board=(int **)calloc(n,sizeof(int*));
	for (int i= 0; i < n; i++)
	    board[i]=(int*)calloc(n,sizeof(int*));
    
    for(int i=0;i<n;i++)
     {for(int j=0;j<n;j++)
      board[i][j]=0;}
      
    solveNQueens();
    delete board;
    
    end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "\nTime taken by program is : " << fixed  
		<< time_taken << setprecision(5); 
	cout << " sec " << endl;
	 
    return 0; 
} 
