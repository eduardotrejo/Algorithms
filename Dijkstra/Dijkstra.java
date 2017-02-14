/* Name: Eduardo Trejo
 * Assignment: 3
 * The program uses the dijkstra algorithm and creates a table from it. It also uses a vertices class.
 */
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Dijkstra {

	static List<Integer> nPrime;
	static List<String> nAlphabet;
	static int stepsTaken = 0;
	static int numberOfVertices = 0, sourceNode;
	static Vertices adjacency_matrix[][];
	static int testingArray[][];
		
	// Create the table and print out results accordingly. 
	public static void drawMatrix()
	{
		System.out.print(stepsTaken + "	");
		for(int i = 0; i < nPrime.size(); i++)
		{
			System.out.print(nAlphabet.get(nPrime.get(i)));
		}
		
		for(int i = 0; i < adjacency_matrix.length; i ++)
		{
			if(adjacency_matrix[sourceNode][i].costCost == 999)
			{
				System.out.print("	∞");
			}
			else if(adjacency_matrix[sourceNode][i].costCost != 0 && !test(i))
			{
				System.out.print("	" + adjacency_matrix[sourceNode][i].costCost + "," + adjacency_matrix[sourceNode][i].source);
			}
			else if(i != sourceNode)
			{
				System.out.print("	   ");
			}
		}
		System.out.println();
		stepsTaken++;
	}
	
	// Used to test if it exists.
	public static boolean test(int temp)
	{
		for(int i = 0; i < nPrime.size(); i++)
		{
			if(nPrime.get(i) == temp)
			{
				return true;
			}
		}
		return false;
	}
	
	public static void main(String[] args){
	
		// Set up variables.
		Scanner scanner = new Scanner(System.in);
		int count, nextNode = 0, newDistance = 999;
		
		// Store the times to loop around
		int loops = 0;
		
		// Read in the input file.
		System.out.print("Enter filename: ");
		String fileName = scanner.next();
		
		FileReader text = null;
		try{
			text = new FileReader(fileName);
			
		}catch(FileNotFoundException e){
			System.out.println("Error opening the file " + fileName);
			System.exit(0);	
			
		}
		
		Scanner source = new Scanner(text);
		loops = Integer.parseInt(source.nextLine());
		numberOfVertices = loops;
		// This array is going to be used to store the file.
		testingArray = new int[numberOfVertices][numberOfVertices];

		// Loops until the certain amount.
		while(loops != 0)
		{
			for(int i = 0; i < numberOfVertices; i++)
			{	
				for(int j = 0; j < numberOfVertices; j++)
				{	
					testingArray[i][j] = source.nextInt();
				}
				loops--;
			}
		}
		
		// Set arrays up.
		adjacency_matrix= new Vertices[numberOfVertices][numberOfVertices];
		nAlphabet = new ArrayList<String>(numberOfVertices);
		nPrime = new ArrayList<Integer>(numberOfVertices);
		boolean visited[] = new boolean[numberOfVertices];
		int distance[] = new int[numberOfVertices];
		
		// Store the characters.
		System.out.println("Enter a character for each of the " + numberOfVertices + " nodes: ");
		
		for(int i = 0; i < numberOfVertices; i++)
		{
			nAlphabet.add(scanner.next());
		}
				
		// Select the starting node.
		System.out.print("Enter the starting node: ");
		sourceNode = scanner.nextInt();
				
		// Values and characters are attached.
		for(int i = 0; i < numberOfVertices; i++)
		{
			for(int j = 0; j < numberOfVertices; j++)
			{
				int m = testingArray[i][j];
				adjacency_matrix[i][j] = new Vertices(m, nAlphabet.get(sourceNode));
			}
		}
		
		// Set up visited.
	    for(int i = 0; i< numberOfVertices; i++)
	    {
	        visited[i] = false;
	    }
	    
	    distance[sourceNode] = 0; 
	    visited[sourceNode] = true;
	    count = 1;
	    nPrime.add(sourceNode);
	    
	    scanner.close();
		
	    
	    int temp = 0;
	    System.out.print("step	N'");
		for(int i = 0; i < nAlphabet.size(); i++)
		{
			if(i != sourceNode)
			{
				System.out.print("	" + nAlphabet.get(i));
			}	
		}
		
		// First Neighbor.
		for(int i = 0; i < numberOfVertices; i++)
		{	
			if(adjacency_matrix[sourceNode][i].costCost != 0 && adjacency_matrix[sourceNode][i].costCost <= newDistance)
			{
				newDistance = adjacency_matrix[sourceNode][i].costCost;
				distance[i] = newDistance;
				nextNode = i;	
			}
		}
		System.out.println();
		visited[nextNode] = true;
			
		while(count < numberOfVertices)
		{
			temp = 999;
			for(int i = 0; i < numberOfVertices; i++)
			{
				if(!visited[i] && adjacency_matrix[sourceNode][i].costCost != 0)
				{
					temp = nPrime.get(nPrime.size() - 1);
					if(adjacency_matrix[sourceNode][i].costCost > adjacency_matrix[sourceNode][temp].costCost + adjacency_matrix[temp][i].costCost)
					{
						adjacency_matrix[sourceNode][i].costCost = adjacency_matrix[sourceNode][temp].costCost + adjacency_matrix[temp][i].costCost;
						adjacency_matrix[sourceNode][i].source = nAlphabet.get(temp);
					}
				}
			}
			temp = 999;
			drawMatrix();
			
			// Determine if there is a better path.
			for(int i = 0; i < numberOfVertices; i++)
			{
				if(adjacency_matrix[sourceNode][i].costCost <= temp && adjacency_matrix[sourceNode][i].costCost != 0 && !test(i))
				{
					temp = adjacency_matrix[sourceNode][i].costCost;
					nextNode = i;
				}
			}
			nPrime.add(nPrime.size(), nextNode);
			count++;
		}
		drawMatrix();
	}
}