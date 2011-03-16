#include <iostream>
#include <sstream>
using namespace std;



string onesDigitToString( char digit )
{
	switch (digit) {
		case '0':	return "";
		case '1':	return "one";
		case '2':	return "two";
		case '3':	return "three";
		case '4':	return "four";
		case '5':	return "five";
		case '6':	return "six";
		case '7':	return "seven";
		case '8':	return "eight";
		case '9':	return "nine";
		default:	return "";
	}
}

string tensDigitToString( char tens, char ones )
{
	if( tens == '1' ) {
		switch (ones) {
			case '0':	return "ten";
			case '1':	return "eleven";
			case '2':	return "twelve";
			case '3':	return "thirteen";
			case '4':	return "fourteen";
			case '5':	return "fifteen";
			case '6':	return "sixteen";
			case '7':	return "seventeen";
			case '8':	return "eighteen";
			case '9':	return "nineteen";
			default:	return "";		
		}
	} else {
		switch (tens) {
			case '2':	return "twenty";
			case '3':	return "thirty";
			case '4':	return "forty";
			case '5':	return "fifty";
			case '6':	return "sixty";
			case '7':	return "seventy";
			case '8':	return "eighty";
			case '9':	return "ninety";
			default:	return "";
		}
	}
}

string hundredsDigitToString( char digit )
{
	return onesDigitToString(digit) + "hundred";
}

string numToWords( int num )
{
	stringstream words; 
	
	if( num > 1000 )
		cerr << "Numbers greater than 1000 not supported";
	
	if( num == 1000 )
		return "onethousand";
	
	// Copy digits to array		
	char digits[4];
	sprintf(digits, "%03d", num);
//	cout << digits << endl;
	
	// Convert hundreds to string
	if( digits[0] != '0' ) {
		words << hundredsDigitToString(digits[0]);
		if( digits[1] != '0' || digits[2] != '0' )
			words << "and";
//		cout << "hundreds digit is " << digits[0] << ", aka " <<
//			hundredsDigitToString(digits[0]) << endl;
	}
	
	// Convert tens to string
	if( digits[1] != '0' ){
		words << tensDigitToString(digits[1], digits[2]);
//		cout << "tens digit is " << digits[1] << ", aka " <<
//			tensDigitToString( digits[1], digits[2] ) << endl;
	}
	
	// Convert ones to string
	if( digits[2] != '0' && digits[1] != '1' ) {
		words << onesDigitToString(digits[2]);
//		cout << "ones digit is " << digits[2] << ", aka " << 
//			onesDigitToString(digits[2]) << endl;
	}
	
   return words.str();
}

int main (int argc, char * const argv[]) {
	int numLetters = 0;
	for( int i = 1; i <= 1000; i++ ) {
		cout << numToWords(i) << endl;
		numLetters += numToWords(i).length();
	}
	cout << numLetters;
	
    return 0;
}
