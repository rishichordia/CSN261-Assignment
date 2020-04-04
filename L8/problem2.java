import java.io.*;
import java.util.*;
class problem2
{
	static HashSet<String> dictionary=new HashSet<String>();
	static HashSet<String> answer=new HashSet<String>();
	static int count;
	public static void main(String ar[])throws Exception
	{
		DataInputStream z1=new DataInputStream(System.in);
		System.out.print("Enter String: ");
		String s=z1.readLine();
		for(int i=0;i<s.length();i++)
			for(int j=i+1;j<s.length();j++)
				if((int)s.charAt(i)>(int)s.charAt(j))
					s=s.substring(0,i)+s.charAt(j)+s.substring(i+1,j)+s.charAt(i)+s.substring(j+1,s.length());
		File fp=new File("dictionary.txt");
		Scanner z=new Scanner(fp);
		while(z.hasNextLine())
		{
			String temp=z.nextLine();
			temp=temp.toLowerCase();
			dictionary.add(temp);
		}
		for(int i=s.length();i>3;i--)
		{
			count=0;
			answer.clear();
			System.out.println("Length: "+i);
			generate_permutations(s,i,"");
			System.out.println();
			System.out.println("Count: "+count);
		}
	
		return;
	}
	public static void generate_permutations(String s,int cnt,String temp)
	{
		if(cnt==0)
		{
			if(dictionary.contains(temp) && !answer.contains(temp))
			{
				System.out.print(temp+" ");
				count++;
				answer.add(temp);
			}
			return;
		}
		for(int i=0;i<s.length();i++)
		{
			String x=s.substring(0,i)+s.substring(i+1,s.length());
			generate_permutations(x,cnt-1,temp+s.charAt(i));
		}
		return;
	}
}
