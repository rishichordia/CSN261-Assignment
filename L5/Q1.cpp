#include<iostream> 
#include<cmath>
using namespace std;
int main() 
{ 
    int n1,n2;


    cout<<"No of terms in the expression:";
    cin>>n1;
    cout<<endl;
    int a1[n1]={-1};
    int c1=n1;
    cout<<"Coefficient Power\n";
    while((--c1)>=0)
    {
    int x,y;
    cin>>x>>y;
    a1[y]=x;
    cout<<endl;
    }


    cout<<"No of terms in the expression:";
    cin>>n2;
    cout<<endl;
    int a2[n2]={-1};
    int c2=n2;
    cout<<"Coefficient Power\n";
    while((--c2)>=0)
    {
    int x,y;
    cin>>x>>y;
    a1[y]=x;
    cout<<endl;
    }


    while(true)
    {cout<<"Enter 1 to add or 2 for multiply"<<endl;
    int y;cin>>y;
    if(y==1)
    {
        int add[max(n1,n2)]={-1};
    for(int i=0;i<max(n1,n2);i++)
    {
        if((n1-1-i)>=0&&(n2-1-i)>=0)
        {
            if(a1[i]!=-1&&a2[i]!=-1)
            add[i]=a1[i]+a2[i];
            else if(a1[i]!=-1)
            add[i]=a1[i];
            else 
            add[i]=a2[i];
        }
        else if((n1-1-i)>=0&&(n2-1-i)<0&&a1[i]!=-1)
        add[i]=a1[i];
        else if((n1-1-i)<0&&(n2-1-i)>=0&&a2[i]!=-1)
        add[i]=a2[i];
    }
    for(int i=max(n1,n2)-1;i>=0;i--)
    {
        if(add[i]!=-1)
        cout<<add[i]<<"\t"<<i<<endl;
    }
    }
    else if(y==2)
    {
        int p[n1+n2-1]={-1};
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<n2;j++)
            {
                if(a1[i]!=-1&&a2[i]!=-1)
                p[i+j]+=(a1[i]*a2[j]);
            }
        }
    for(int i=n1+n2-2;i>=0;i--)
    {
        if(p[i]!=-1)
        cout<<p[i]<<"\t"<<i<<endl;
    }
    }
    }
    return 0; 
}