#include <iostream>
#include <string>
#include "bigint-3-0-src/bigint.h"

ulong sumOfDigits( string number ) 
{
	ulong sum = 0;
	unsigned int sLength = number.length();
	char c[2] = { '0', '\0' };
	
	for( int i = 0; i < sLength; i++ ) {
		c[0] = number.at(i);
		sum += atoi( c );
	}
	
	return sum;
}

RossiBigInt twoToTheNthPower( unsigned int exponent ) 
{
	RossiBigInt product( 1 );
	for( int i = 1; i <= exponent; i++ )
	{
		product = product * 2;
	}
	
	return product;
}

int main (int argc, char * const argv[]) {
	cout << "Sum of 32768 is " << sumOfDigits("32768") << endl;
	
	RossiBigInt twoToThe1000 = twoToTheNthPower(1000);
	cout << "2 to the 1000 is " << twoToThe1000 << endl;
	
	stringstream buf; 
	buf << twoToThe1000;
	string twoToThe1000String = buf.str();
	cout << "Sum of the digits is " << sumOfDigits( twoToThe1000String ) << endl;
	
    std::cout << "Hello, World!\n";
    return 0;
}
