import java.util.*;
class problem2
{
	static int arr[];
	static int min_segtree[];
	static int max_segtree[];
	static int sum_segtree[];
	static int lazy[];
	public static void build(int t,int tl,int tr)
	{
		if(tl==tr)
		{
			min_segtree[t]=arr[tl];
			max_segtree[t]=arr[tl];
			sum_segtree[t]=arr[tl];
			return;
		}
		int tm=(tl+tr)/2;
		build(2*t,tl,tm);
		build(2*t+1,tm+1,tr);
		min_segtree[t]=Math.min(min_segtree[2*t],min_segtree[2*t+1]);
		max_segtree[t]=Math.max(max_segtree[2*t],max_segtree[2*t+1]);
		sum_segtree[t]=sum_segtree[2*t]+sum_segtree[2*t+1];
		return;
	}
	public static void push(int t,int tl,int tr)
	{
		if(lazy[t]==0)
			return;
		if(tl!=tr)
		{
			lazy[2*t]+=lazy[t];
			lazy[2*t+1]+=lazy[t];
			int tm=(tl+tr)/2;
			sum_segtree[2*t]+=(tm-tl+1)*lazy[t];
			sum_segtree[2*t+1]+=(tr-tm)*lazy[t];
			min_segtree[2*t]+=lazy[t];
			max_segtree[2*t]+=lazy[t];
			min_segtree[2*t+1]+=lazy[t];
			max_segtree[2*t+1]+=lazy[t];
		}
		lazy[t]=0;
		return;
	}
	public static int query(int t,int tl,int tr,int l,int r,int type)
	{
		if(l>r)
		{
			if(type==1)
				return 10000;
			else if(type==2)
				return -10000;
			else
				return 0;
		}
		if(l==tl && r==tr)
		{
			if(type==1)
				return min_segtree[t];
			else if(type==2)
				return max_segtree[t];
			else
				return sum_segtree[t];
		}
		push(t,tl,tr);
		int tm=(tl+tr)/2;
		int q1=query(2*t,tl,tm,l,Math.min(r,tm),type);
		int q2=query(2*t+1,tm+1,tr,Math.max(l,tm+1),r,type);
		if(type==1)
			return Math.min(q1,q2);
		else if(type==2)
			return Math.max(q1,q2);
		else
			return q1+q2;
	}
	public static void update(int t,int tl,int tr,int l,int r)
	{
		if(l>r)
			return;
		if(l==tl && r==tr)
		{
			lazy[t]+=4;
			sum_segtree[t]+=(tr-tl+1)*4;
			min_segtree[t]+=4;
			max_segtree[t]+=4;
			return;
		}
		push(t,tl,tr);
		int tm=(tl+tr)/2;
		update(2*t,tl,tm,l,Math.min(r,tm));
		update(2*t+1,tm+1,tr,Math.max(tm+1,l),r);
		min_segtree[t]=Math.min(min_segtree[2*t],min_segtree[2*t+1]);
		max_segtree[t]=Math.max(max_segtree[2*t],max_segtree[2*t+1]);
		sum_segtree[t]=sum_segtree[2*t]+sum_segtree[2*t+1];
		return;
	}
	public static void main(String args[])
	{
		Scanner z=new Scanner(System.in);
		int n=z.nextInt();
		arr=new int[n];
		for(int i=0;i<n;i++)
			arr[i]=z.nextInt();
		min_segtree=new int[5*n];
		max_segtree=new int[5*n];
		sum_segtree=new int[5*n];
		lazy=new int[5*n];
		build(1,0,n-1);
		int ch,l=0,r=0;
		do
		{
			System.out.println("1 - Find minimum value");
			System.out.println("2 - Find maximum value");
			System.out.println("3 - Find sum");
			System.out.println("4 - Update by adding 4");
			System.out.println("5 - Exit");
			ch=z.nextInt();
			if(ch>0 && ch<5)
			{
				System.out.println("Enter range");
				System.out.print("Index 1 : ");
				l=z.nextInt();
				System.out.print("Index 2 : ");
				r=z.nextInt();
			}
			if((ch>0 && ch<5) && (l>r || l<0 || r>=n))
			{
				System.out.println("Invalid Index");
				continue;
			}
			switch(ch)
			{
				case 1:
				{long startTime=System.nanoTime();
				System.out.print("Minimum is : ");
				System.out.println(query(1,0,n-1,l,r,1));
				long endTime=System.nanoTime();
				long timeElapsed=endTime-startTime;
				System.out.println("Execution time :"+timeElapsed+" ns");
				break;}
				case 2:
				{long startTime=System.nanoTime();
				System.out.print("Maximum is : ");
				System.out.println(query(1,0,n-1,l,r,2));
				long endTime=System.nanoTime();
				long timeElapsed=endTime-startTime;
				System.out.println("Execution time :"+timeElapsed+" ns");
				break;}
				case 3:
				{long startTime=System.nanoTime();
				System.out.print("Sum is : ");
				System.out.println(query(1,0,n-1,l,r,3));
				long endTime=System.nanoTime();
				long timeElapsed=endTime-startTime;
				System.out.println("Execution time :"+timeElapsed+" ns");
				break;}
				case 4:
				{long startTime=System.nanoTime();
				update(1,0,n-1,l,r);
				long endTime=System.nanoTime();
				long timeElapsed=endTime-startTime;
				System.out.println("Execution time :"+timeElapsed+" ns");
				break;}
				default:
				break;
			}
		}
		while(ch!=5);
		return;	
	}
}
