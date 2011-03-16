package net.autumncloud.ProjectEuler;

public class Problem67App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String fileName = "/Users/sam/Source/ProjectEuler/triangle.txt";
		
		NumberTriangle triangle = NumberTriangle.numberTriangleFromTextFile(fileName);  
		
		System.out.println( "Initialized Number Triangle\n" + triangle );
		
		int size = triangle.size();
		System.out.println( "Size is " + size );
		//assert size == 10;
		
		int height = triangle.height();
		System.out.println( "Height is " + height );
		//assert height == 4;
		
		NumberTriangleNodePath maxPath = triangle.maxPath();
		System.out.println( "Max path is " + maxPath + " (" + maxPath.getSumTotal() + ")" );
		//assert maxPath.getSumTotal() == 23;
	}

}
