// ==============================================================
//
//  Copyright (C) 1995  William A. Rossi
//                      Class RossiBigInt
// 
//  Copyright (C) 1999-2009  Alex Vinokur
//                           Class VinBigInt
//                           Upgrading class RossiBigInt
//
//  ------------------------------------------------------------
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//  ------------------------------------------------------------
// 
//  mailto:alex DOT vinokur AT gmail DOT com
//  http://up.to/alexv
//
// ==============================================================
#define BIG_INT_VERSION_No "3.0"


// ##############################################################
//
//  SOFTWARE : Class BigInt
//  FILE     : bigint.h
//
//  DESCRIPTION :
//          Classes VinBigInt & RossiBigInt (Declarations)
//
// ##############################################################


///////////////////////////////////////

#ifndef BIGINT_H
#define BIGINT_H

///////////////////////////////////////


#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;


// =======
// DEFINES
// =======
#define ASSERTION(x) 	 if (!(x)) \
			 { \
			 assert(x); \
			 cerr << "[" \
			      << __FILE__ \
			      << ", " \
			      << __LINE__  \
			      << "] assert() not working" \
			      << endl;  \
			      abort(); \
			 }


#define DEC_DIGIT 10
#define HEX_DIGIT 16

#define MAX_VAL(x,y)  ((x) > (y) ? (x) : (y))
#define MIN_VAL(x,y)  ((x) < (y) ? (x) : (y))

#define CERR cerr << "[ " << __FILE__ << ", " << setw(3) << std::right << __LINE__ << " ] "
#define FATAL_ERROR(t) cerr << endl; CERR << "FATAL ERROR : " << t << endl

// ========
// TYPEDEFS
// ========
typedef unsigned long ulong;



///////////////
// DECLARATIONS
///////////////

class BaseBigInt;
class VinBigInt;
class RossiBigInt;

void ShowVersion();


// ==============
class BaseBigInt
// ==============
{

  protected :
    vector<ulong> units_;
    static map<char, ulong> hex_to_dec_digits_convertor_s;

    ulong get_units_size () const;

    virtual ~BaseBigInt () = 0;


  public :
    bool  is_empty () const;

};



// ==============
class VinBigInt : public BaseBigInt
// ==============
{
friend ostream& operator<< (ostream& os, const VinBigInt& ins_i);


  private :
    bool init_via_string (const string& arg_i, ulong digit_base_i);

  public :
    // --- Constructors ---
    explicit VinBigInt ();
    explicit VinBigInt (ulong unit_i);
    explicit VinBigInt (const string& arg_i, ulong digit_base_i);
    explicit VinBigInt (const RossiBigInt& arg_i);


    // --- Aux methods  ---
    ulong get_pure_ulong () const;
    // operator ulong () const;


    // --- General purpose mathematical methods ---
    VinBigInt operator+ (const VinBigInt& arg_i) const;
    VinBigInt operator* (ulong arg_i) const;


    // --- Comparison operators ---
    bool operator== (const VinBigInt& arg_i) const;
    bool operator!= (const VinBigInt& arg_i) const;
    bool operator<  (const VinBigInt& arg_i) const;
    bool operator>  (const VinBigInt& arg_i) const;
    bool operator<= (const VinBigInt& arg_i) const;
    bool operator>= (const VinBigInt& arg_i) const;

    // --- Test functions ---
    static void All_Tests ();
    static void Test100_Operator_Add_Bigint ();
    static void Test300_Operator_Multiplication_Ulong ();

};


// ==============
class RossiBigInt : public BaseBigInt
// ==============
{
friend ostream& operator<< (ostream& os, const RossiBigInt& ins_i);

  private :
    // --- Aux methods ---
    void  resize_units (ulong size_i);
    void  truncate_units ();
    bool  units_not_front_back_is_null () const;
    bool  init_via_string (const string& arg_i, ulong digit_base_i);


  public :

    // --- Constructors ---

    explicit RossiBigInt ();
    explicit RossiBigInt (ulong unit_i);
    explicit RossiBigInt (const string& arg_i, ulong digit_base_i);
    explicit RossiBigInt (const VinBigInt& arg_i);


    // --- Aux methods ---
    ulong get_pure_ulong () const;
    // operator ulong () const;


    // --- General purpose mathematical methods ---

    // RossiBigInt& operator= (ulong arg_i);
    RossiBigInt  operator+ (const RossiBigInt& arg_i);
    RossiBigInt  operator+ (ulong arg_i);
    RossiBigInt  operator* (RossiBigInt arg_i) const;
    RossiBigInt  operator* (ulong arg_i) const;
    //  RossiBigInt& RossiBigInt::operator*= (RossiBigInt arg_i);
    RossiBigInt operator/ (const RossiBigInt& arg_i) const;
    RossiBigInt operator% (const RossiBigInt& arg_i) const;
    RossiBigInt  Divide(const RossiBigInt& dividend_i, const RossiBigInt& divisor_i, RossiBigInt* remainder_o) const;
    RossiBigInt& operator+= (const RossiBigInt& arg_i);
    RossiBigInt  operator++ (int); // Post increment operator
    RossiBigInt& operator++ ();    // Pre increment operator
    RossiBigInt  operator-  (const RossiBigInt& arg_i);
    RossiBigInt  operator-  ();
    RossiBigInt  operator-- (int); // Post decrement operator
    RossiBigInt& operator-- ();    // Pre decrement operator
    RossiBigInt& operator-= (const RossiBigInt& arg_i);
    RossiBigInt  sqrt();



    // --- Bitwise boolean operators ---

    RossiBigInt  operator&   (const RossiBigInt& arg_i);
    RossiBigInt  operator|   (const RossiBigInt& arg_i);
    RossiBigInt  operator^   (const RossiBigInt& arg_i);
    RossiBigInt& operator&=  (const RossiBigInt& arg_i);
    RossiBigInt& operator|=  (const RossiBigInt& arg_i);
    RossiBigInt& operator^=  (const RossiBigInt& arg_i);
    RossiBigInt  operator~   ();
    RossiBigInt  operator>>  (ulong shift_i);
    RossiBigInt  operator<<  (ulong shift_i);
    RossiBigInt& operator>>= (ulong shift_i);
    RossiBigInt& operator<<= (ulong shift_i);



    // --- Comparison operators ---

    bool operator== (const RossiBigInt& arg_i) const;
    bool operator!= (const RossiBigInt& arg_i) const;
    bool operator<  (const RossiBigInt& arg_i) const;
    bool operator>  (const RossiBigInt& arg_i) const;
    bool operator<= (const RossiBigInt& arg_i) const;
    bool operator>= (const RossiBigInt& arg_i) const;

    // --- Show functions ---
    string getstr_pure_hex_value () const;
    string getstr_hex_value () const;

    // --- Test functions ---
		static void assertCheck();
    void dbg_show () const;
    static void All_Tests ();
    static void Test100_Operator_Add_Bigint ();
    static void Test200_Operator_Subtraction_Bigint ();
    static void Test210_Operator_Subtraction_Bigint ();
    static void Test300_Operator_Multiplication_Bigint ();
    static void Test400_Operator_Division_Bigint ();
    static void Test500_Operator_Reminder_Bigint ();
    static void Test600_Operator_Less ();
    static void Compilation_Test ();


};


// ==================
#endif	// BIGINT_H
// ==================


