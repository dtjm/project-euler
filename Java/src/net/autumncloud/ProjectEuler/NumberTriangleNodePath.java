package net.autumncloud.ProjectEuler;

import java.util.ArrayList;

/**
 * @author sam
 *
 */
public class NumberTriangleNodePath {

	private ArrayList<NumberTriangleNodeInterface> treeNodeArray;
	//private int iteratorIndex = 0;
	private int sumTotal = 0;
	
	public NumberTriangleNodePath()
	{
		treeNodeArray = new ArrayList<NumberTriangleNodeInterface>();
	}
	
	// Constructor with initial node element
	public NumberTriangleNodePath( NumberTriangleNodeInterface node ) 
	{
		this();
		this.addNodeToPath( node );
	}
	
	// Copy constructor
	@SuppressWarnings("unchecked")
	public NumberTriangleNodePath( NumberTriangleNodePath path )
	{
		this.treeNodeArray = (ArrayList<NumberTriangleNodeInterface>) path.treeNodeArray.clone();
		this.sumTotal = path.getSumTotal();
	}
	
//	public NumberTriangleNodeInterface nextNodeInPath() 
//	{
//		return treeNodeArray.get( iteratorIndex++ );
//	}
//	
//	public void rewind()
//	{
//		this.iteratorIndex = 0;
//	}
	
	public void addNodeToPath( NumberTriangleNodeInterface node )
	{
		this.treeNodeArray.add( node );
		this.sumTotal += node.getValue();
	}
	
	public NumberTriangleNodeInterface lastNodeInPath()
	{
		// Return the last item in the array
		return treeNodeArray.get( treeNodeArray.size() - 1 );
	}
	
	public int getSumTotal() 
	{
		return this.sumTotal;
	}
	
	@Override public String toString()
	{
		return this.treeNodeArray.toString();
	}
}
