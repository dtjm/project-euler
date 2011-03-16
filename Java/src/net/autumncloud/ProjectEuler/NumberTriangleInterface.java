package net.autumncloud.ProjectEuler;

import java.util.ArrayList;

public interface NumberTriangleInterface {
	abstract int size();
	abstract int height();
	abstract int appendNode( NumberTriangleNodeInterface t );
	abstract ArrayList<NumberTriangleNodeInterface> nodesAtHeight( int height );
	abstract NumberTriangleNodeInterface nodeAtHeightAndIndex( int height, int index );
}
