import java.util.*;
class bruteproblem2
{
	public static void main(String args[])
	{
		
	
	
		Scanner z=new Scanner(System.in);
		int n=z.nextInt();
		int arr[]=new int[n];
		for(int i=0;i<n;i++)
			arr[i]=z.nextInt();
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
				{
					long startTime=System.nanoTime();
					int mi=10000;
					for(int i=l;i<=r;i++)
						mi=Math.min(mi,arr[i]);
					System.out.println("Minimum is : "+mi);
					long endTime=System.nanoTime();
					long timeElapsed=endTime-startTime;
					System.out.println("Execution time :"+timeElapsed+" ns");
					break;
				}
				case 2:
				{
					long startTime=System.nanoTime();
					int mx=-10000;
					for(int i=l;i<=r;i++)
						mx=Math.max(mx,arr[i]);
					System.out.println("Maximum is : "+mx);
					long endTime=System.nanoTime();
					long timeElapsed=endTime-startTime;
					System.out.println("Execution time :"+timeElapsed+" ns");
					break;
				}
				case 3:
				{
					long startTime=System.nanoTime();
					int sm=0;
					for(int i=l;i<=r;i++)
						sm+=arr[i];
					System.out.println("Sum is : "+sm);
					long endTime=System.nanoTime();
					long timeElapsed=endTime-startTime;
					System.out.println("Execution time :"+timeElapsed+" ns");
					break;
				}
				case 4:
				{
					long startTime=System.nanoTime();
					for(int i=l;i<=r;i++)
						arr[i]+=4;
					long endTime=System.nanoTime();
					long timeElapsed=endTime-startTime;
					System.out.println("Execution time :"+timeElapsed+" ns");
					break;
				}
				default:
				break;
			}
		}
		while(ch!=5);
	
	return;
	}
}
