package net.autumncloud.ProjectEuler;


/**
 * @author sam
 * How a Tree Node should behave
 */
public interface NumberTriangleNodeInterface {
	abstract int getValue();
	
	abstract NumberTriangleNodeInterface getLeftParent();
	abstract void setLeftParent( NumberTriangleNodeInterface node );
	abstract NumberTriangleNodeInterface getRightParent();
	abstract void setRightParent( NumberTriangleNodeInterface node );
	
	abstract void setLeftChild( NumberTriangleNodeInterface n );
	abstract NumberTriangleNodeInterface getLeftChild();
	abstract void setRightChild( NumberTriangleNodeInterface n );	
	abstract NumberTriangleNodeInterface getRightChild();
}
