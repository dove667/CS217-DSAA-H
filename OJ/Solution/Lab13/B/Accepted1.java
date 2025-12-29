import java.io.*;
import java.util.*;

/* Ioana, 1 BFS*/

public class Accepted1
{
	static class AdjList
	{
		int m_count;
		int[] m_members;
		public AdjList() {
			m_count = 0;
		}
	}

	static int N, M;
	static int[] levels;
	static int[] queue;
	static int[][] edges;
	static AdjList[] neighbours; 
	
	static int longestshortest(int startvertex)
	{
		for (int i = 0; i<N;++i)
			levels[i] = 0;
		
		int first = 0, last = 0;  
		queue[0] = startvertex;
		levels[startvertex] = 1;  
    	while (first <= last) {
    		int crt = queue[first];
    		for (int i = 0; i < neighbours[crt].m_count; ++i) {
    			int crtneighb = neighbours[crt].m_members[i];
    			if (levels[crtneighb] == 0) {
    				queue[++last] = crtneighb;
    				levels[crtneighb] = levels[crt]+1;
    			}

    		}   
    		++first;               
    	}
    	if (last < N-1)
    		return 0;
    	return levels[queue[last]];
	}

	static void readAndProcess() {
	    try {
	        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    
            StringTokenizer stringtokenizer = new StringTokenizer(br.readLine());
            N = Integer.parseInt(stringtokenizer.nextToken());
            M = Integer.parseInt(stringtokenizer.nextToken());
		
		    levels = new int[N];
	        queue = new int[N];
	        edges = new int[M][2];
		    neighbours = new AdjList[N];
		
		    for (int i = 0; i < N; ++i)
			    neighbours[i] = new AdjList();
		
		    for (int i = 0; i < M; ++i){
		        stringtokenizer = new StringTokenizer(br.readLine());
	            int r1 = Integer.parseInt(stringtokenizer.nextToken());
                int r2 = Integer.parseInt(stringtokenizer.nextToken());
	            r1--;
	            r2--;
	            edges[i][0]=r1;
	            edges[i][1]=r2;
	            neighbours[r1].m_count++;
	             neighbours[r2].m_count++;
	        }
	    } catch(Exception exception) { }
        
	
		for (int i = 0; i < N; ++i) { 
	        neighbours[i].m_members = new int[neighbours[i].m_count];
	        neighbours[i].m_count = 0;
	    }
	    
	    for (int i = 0; i < M; ++i) {
	        neighbours[edges[i][0]].m_members[neighbours[edges[i][0]].m_count++] = edges[i][1];
	        neighbours[edges[i][1]].m_members[neighbours[edges[i][1]].m_count++] = edges[i][0];
	    }
	}
	
	public static void main(String[] args) throws FileNotFoundException
	{
		readAndProcess();
		int estimatediam = longestshortest(0)-1;
    
		if (estimatediam == -1) 
			System.out.println("-1\n");
		else {
			double log2 = Math.log(estimatediam) / Math.log(2);
			System.out.println((int)Math.ceil(log2)+1); 
		}
	}
}

