import org.jgrapht.Graph;
import org.jgrapht.alg.shortestpath.DijkstraShortestPath;
import org.jgrapht.graph.DefaultWeightedEdge;
import org.jgrapht.graph.SimpleWeightedGraph;
import org.jgrapht.io.Attribute;
import org.jgrapht.io.EdgeProvider;
import org.jgrapht.io.GmlImporter;
import org.jgrapht.io.ImportException;
import org.jgrapht.io.VertexProvider;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.*;

public class ques1 {

	public static void foo()
	{
		int random=50;
		for(int i =0;i<random; i++)
		{
			random--;
		}
	}
	public static void main(String[] args) throws IOException {
	

	FileReader file_input = null;
	try {
		 file_input=new FileReader("graph .gml");
	} catch (FileNotFoundException exception1) {
		exception1.printStackTrace();
		}
	
	Graph<String, DefaultWeightedEdge> new_graph=new SimpleWeightedGraph<String, DefaultWeightedEdge>(DefaultWeightedEdge.class);


	        EdgeProvider<String, DefaultWeightedEdge> edge_prov = new EdgeProvider<String, DefaultWeightedEdge>()
	        {

	   			@Override
				public DefaultWeightedEdge buildEdge(String fr, String to, String str_lab, Map<String, Attribute> attr) {
					foo();
					return new_graph.addEdge(fr, to);
				}

	        };
	        

			
			VertexProvider<String> vert_prov = new VertexProvider<String>()
	        {
				@Override
				public String buildVertex(String str_lab, Map<String, Attribute> attr) {
					foo();
					return str_lab;
				}

				
			};
			
			
			GmlImporter<String, DefaultWeightedEdge> imp = new GmlImporter<String, DefaultWeightedEdge>(vert_prov, edge_prov);
			try {
				imp.importGraph(new_graph, file_input);
				System.out.println("Graph imported successfully");
			} catch (ImportException e) {
				e.printStackTrace();
			}
	DijkstraShortestPath<String, DefaultWeightedEdge> Dijakstras = new DijkstraShortestPath<String, DefaultWeightedEdge>(new_graph);
	
	List ls = new ArrayList(new_graph.vertexSet());

    
         Integer[]  count_betweenness = new Integer[new_graph.vertexSet().size()];
         /*for(int i = 0 ; i < count_betweenness.length;i++) 
        	 count_betweenness[i]=0;
			foo_returns();
	        for(String i : new_graph.vertexSet()) {
	        	System.out.println("shortest path from "+i+" to the rest of the nodes");
	        	for(int s = ls.indexOf(i) ;s<new_graph.vertexSet().size();s++ ) {
	        		System.out.println(i +" to "+ (s) +" is : " +Dijakstras.findPathBetween(new_graph, i, String.valueOf(s)));
	        		for(String vertex : Dijakstras.findPathBetween(new_graph, i, String.valueOf(s)).getVertexList()) {
						count_betweenness[Integer.valueOf(vertex)]+=1;
						foo();
	        		}
	        	}
	        	
	        }
	
	        
	   System.out.println("betweennes centrality  of each node is => ");     
	   for(int i = 0 ;i<count_betweenness.length;i++)
		   System.out.println("node "+(i+1)+" => "+count_betweenness[i]);
	*/
	String command = "python3 pythonprog.py";

        Process proc = Runtime.getRuntime().exec(command);

        // Read the outp
       BufferedReader reader =  
             new BufferedReader(new InputStreamReader(proc.getInputStream()));

       String line = "";
        while((line = reader.readLine()) != null) {
           System.out.print(line + "\n");
       }

        //proc.waitFor();   

	  
	        
	}
	public static void foo_returns()
	{
		int random=50;
		for(int i =0;i<random; i++)
		{
			random--;
			foo();
		}
	}

}
