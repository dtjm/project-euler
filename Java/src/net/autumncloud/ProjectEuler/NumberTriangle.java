package net.autumncloud.ProjectEuler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringTokenizer;

public class NumberTriangle {
	
	ArrayList<NumberTriangleNodeInterface> nodeArray;
	
	public NumberTriangle( int... nodeValues ) 
	{
		this.nodeArray 			= new ArrayList<NumberTriangleNodeInterface>( nodeValues.length );
		
		int leftParentIndex 		= -2;	// Compensate for node #1
		int rightParentIndex 		= -1;
		int leftParentLowerBound 	= 0;
		int rightParentUpperBound 	= 0;
		
		for( int val : nodeValues ) {
			// Create and add node
			NumberTriangleNode newNode = new NumberTriangleNode( val );
			this.nodeArray.add( newNode );

			// SET PARENT NODES
			// Set left parent & child relationship if its in range
			if( leftParentIndex >= leftParentLowerBound ) {
				NumberTriangleNodeInterface leftParent = this.nodeArray.get( leftParentIndex );
				newNode.setLeftParent( leftParent );
				leftParent.setRightChild( newNode );
			}
			
			leftParentIndex++;
			
			// Set right parent & child relationship
			if( rightParentIndex <= rightParentUpperBound && rightParentIndex >= 0 ) {
				NumberTriangleNodeInterface rightParent = this.nodeArray.get( rightParentIndex );
				newNode.setRightParent( rightParent );
				rightParent.setLeftChild( newNode );
			}	
			
			rightParentIndex++;
			
			if( rightParentIndex == rightParentUpperBound + 2 ) { // reset bounds
				leftParentLowerBound  = NumberTriangle.startIndexOfRow( this.height() );
				rightParentUpperBound = NumberTriangle.endIndexOfRow( 	this.height() );
				
				leftParentIndex = leftParentLowerBound - 1;
				rightParentIndex = NumberTriangle.startIndexOfRow( this.height() );
			}					
		}
	}
	
	public static NumberTriangle numberTriangleFromTextFile(String fileName) {
			
		ArrayList<Integer> numbersArray = new ArrayList<Integer>();
		
		BufferedReader fileReader;
		try {
			  fileReader = new BufferedReader( new FileReader(fileName) );
		}
		catch(FileNotFoundException e) {
			System.out.println( String.format("Couldn't read file '%s'", fileName) );
			return null;
		}
		
		try {
			while( fileReader.ready() ) {
				String line = fileReader.readLine();
				
				StringTokenizer tokenizer = new StringTokenizer(line);
						
				while( tokenizer.hasMoreTokens() ) {
					
					numbersArray.add( Integer.parseInt( tokenizer.nextToken() ) ); 
			
				}
				
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
		
		int[] intArray = new int[numbersArray.size()];
		int arrayInsertIndex = 0;
		for( int i : numbersArray ) {
			intArray[arrayInsertIndex++] = i;
		}
		
		return new NumberTriangle( intArray );
	}
	
	public int size()
	{
		return this.nodeArray.size();
	}
	
	public int height() 
	{
		int height 		= 0;
		int upperBound 	= 0;
		int rowSize 	= 1; 
		
		while( upperBound < this.size() ) {
			height++;
			upperBound += rowSize++;			
		}
		
		return height;
	}
	
	private static int startIndexOfRow( int height )
	{
		int startIndex = 0;
		
		height--;
		
		while( height > 0 ) {
			
			startIndex += height--;
			
		}
		
		return startIndex;
	}
	
	private static int endIndexOfRow( int height )
	{		
		int endIndex = -1;
		
		while( height > 0 ) {
		
			endIndex += height--;
		
		}	
	
		return endIndex;
		
	}
	
	public ArrayList<NumberTriangleNodeInterface> nodesAtHeight( int height )
	{
		int rowStartIndex = NumberTriangle.startIndexOfRow( height );

		int rowEndIndex = NumberTriangle.endIndexOfRow( height );
		
		ArrayList<NumberTriangleNodeInterface> nodesToReturn = new ArrayList<NumberTriangleNodeInterface>( rowEndIndex - rowStartIndex + 1 );
		
		// Copy nodes from nodesArray to return array
		for( int i = rowStartIndex; i <= rowEndIndex; i++ ) {
			nodesToReturn.add( this.nodeArray.get( i ) );
		}
		
		return nodesToReturn;
	}
	
	public NumberTriangleNodePath maxPath() 
	{
		// Create a map of node paths, keyed to the root node of the path
		HashMap<NumberTriangleNodeInterface, NumberTriangleNodePath> maxPathWithStartingNode = new HashMap<NumberTriangleNodeInterface, NumberTriangleNodePath>();
		
		for( int currHeight = this.height(); currHeight > 0; currHeight-- ) {

			// Get the nodes at this height
			ArrayList<NumberTriangleNodeInterface> baseNodes = this.nodesAtHeight( currHeight );

			for( NumberTriangleNodeInterface node : baseNodes ) {
			
				// Create nodepath branch with left and right children
				NumberTriangleNodeInterface leftChild = node.getLeftChild();
				int pathSumTotal = -1;
				if( leftChild != null ) {
					NumberTriangleNodePath pathFromLeft = new NumberTriangleNodePath( maxPathWithStartingNode.get( leftChild ) );
					pathFromLeft.addNodeToPath( node );
					
					maxPathWithStartingNode.put( node, pathFromLeft );
					pathSumTotal = pathFromLeft.getSumTotal();
				}
				
				NumberTriangleNodeInterface rightChild = node.getRightChild();
				if( rightChild != null ) {
					NumberTriangleNodePath pathFromRight = new NumberTriangleNodePath( maxPathWithStartingNode.get( rightChild ) );
					pathFromRight.addNodeToPath( node );
				
					if( pathFromRight.getSumTotal() > pathSumTotal )
						maxPathWithStartingNode.put( node, pathFromRight );
				}
									
				// Or else create a new nodepath with a single node 
				if( leftChild == null && rightChild == null ) {
					NumberTriangleNodePath newPath = new NumberTriangleNodePath( node );
					maxPathWithStartingNode.put( node, newPath );
				}				
			}	
		}
		
		NumberTriangleNodeInterface rootNode = this.nodeArray.get( 0 );
		return maxPathWithStartingNode.get( rootNode );
	}
	
	@Override
	public String toString()
	{
		StringBuilder stringBuilder = new StringBuilder( 3 * this.size() );
		
		int currHeight = 1;
		int indexCounter = 1;
		
		for( NumberTriangleNodeInterface node : this.nodeArray ) {
			stringBuilder.append( node );
			
			indexCounter--;
			
			if( 0 == indexCounter ) {
				stringBuilder.append( "\n" );
				currHeight++;
				indexCounter = currHeight;
			}
			else {
				stringBuilder.append( ' ' );
			}
		}
		
		return stringBuilder.toString();
	}
	
}
