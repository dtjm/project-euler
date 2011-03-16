package net.autumncloud.ProjectEuler;

import java.math.BigInteger;

public class Problem20App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		// Calculate the factorial
		BigInteger factorial = bigIntegerFactorial( 100 ); 
					
		// Sum the digits
		long sum = 0;
		String factorialString = factorial.toString();
		for( int i = 0; i < factorialString.length(); i++ ) {
			sum += Integer.parseInt( factorialString.substring(i, i+1) );
		}
			
		// Print it out
		System.out.println( "Sum of digits of " + factorial + " is " + sum);
	}
	
	static BigInteger bigIntegerFactorial( int arg ) {
		return bigIntegerFactorial( BigInteger.valueOf(arg) );
	}
	
	static BigInteger bigIntegerFactorial( BigInteger arg ) {
		if( arg.equals( BigInteger.ZERO )
				|| arg.equals( BigInteger.ONE ) )
			return BigInteger.ONE;

		else 
			return arg.multiply( bigIntegerFactorial( arg.subtract(BigInteger.ONE) ) );
	}

}
