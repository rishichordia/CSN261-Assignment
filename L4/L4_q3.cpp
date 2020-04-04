#include <iostream>
#include <unordered_map>
#include<iomanip>
#include<time.h> 
using namespace std;

int start_index;//!Stores the starting index
int end_index;//!Stores the end index of the occurence
/*!A function that finds the longest subarray in with a given sum from the Array
@param arr This is the array on which we have to operate
@param n This is the number of elememts given in the array
@param given_sum This is the sum that we have to find
*/
int findLongestArray(int n,int arr[],int given_sum) 
{
    unordered_map<int, int> m; 
    int sum = 0, maxLen = 0; 
  
     for (int i = 0; i < n; i++) { 
  
        sum += arr[i];
        //!Stores the sum in the hash map
        if (m.find(sum) == m.end()) 
            m[sum] = i;
	//!Checks if the sum is the required sum
	if (sum == given_sum) {
	    maxLen = i + 1;
            end_index=i;}
        
        //!Finds whether the amount by which the sum is short or more present in the hash table
        //!If present updates the hash Table    
        if (m.find(sum - given_sum) != m.end()) 
        { 

            if (maxLen < (i - m[sum - given_sum]))
                 {
                 maxLen = i - m[sum - given_sum];
                 end_index=i;
                 }          
         } 
    }
    start_index=end_index-maxLen+1;
    return maxLen;
} 
//!The main function is the driver that drives the program by taking required input and also calculates the execution time
int main() 
{
	clock_t start, end; 
	start = clock(); 

    start_index=-1;end_index=-1; 
    int n;
    cin>>n;
    int arr[n] = {};
    for(int i=0;i<n;i++)
     cin>>arr[i]; 
    int k;
    cin>>k;
    int maxLen=findLongestArray(n,arr,k);
    if(maxLen)
    {
    	cout << "\nLength of the longest subarray is "
        	 <<maxLen<<endl; 
     	cout<<"Index from "<<start_index<<" to "<<end_index<<endl;
    }
    else
    	cout<<"Sum not Found"<<endl;
    	
    	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
	cout << "\nTime taken by program is : " << fixed  
		<< time_taken << setprecision(5); 
	cout << " sec " << endl;
    return 0; 
}
