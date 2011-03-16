package net.autumncloud.ProjectEuler;

public class NumberTriangleNode implements NumberTriangleNodeInterface {

	int value;
	NumberTriangleNode leftChild;
	NumberTriangleNode rightChild;
	NumberTriangleNode leftParent;
	NumberTriangleNode rightParent;
	
	public NumberTriangleNode( int val ) {
		this.value = val;
	}
	
	public int getValue() { return this.value; }
	
	public void setLeftChild( NumberTriangleNodeInterface t )
	{
		this.leftChild = (NumberTriangleNode) t;
	}
	
	public NumberTriangleNode getLeftChild() 
	{
		return this.leftChild;
	}
	
	public void setRightChild( NumberTriangleNodeInterface t )
	{
		this.rightChild = (NumberTriangleNode) t;
	}
	
	public NumberTriangleNode getRightChild()
	{
		return this.rightChild;
	}
	
	public NumberTriangleNode getLeftParent()
	{
		return this.leftParent;		
	}
	
	public void setLeftParent( NumberTriangleNodeInterface node )
	{
		this.leftParent = (NumberTriangleNode) node;
	}
	
	public NumberTriangleNode getRightParent()
	{
		return this.rightParent;		
	}
	
	public void setRightParent( NumberTriangleNodeInterface node )
	{
		this.rightParent = (NumberTriangleNode) node;
	}
	
	@Override public String toString() 
	{
		return Integer.toString( this.value );
	}

}
