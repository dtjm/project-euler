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


// ##############################################################
//
//  SOFTWARE : Class BigInt
//  FILE     : bigint.cpp
//
//  DESCRIPTION :
//          Classes VinBigInt & RossiBigInt (Definitions)
//
// ##############################################################


// ================
#include "bigint.h"
// ================


//////////
// DEFINES
//////////

// ==================

#define MAX_UNIT_VALUE  (ULONG_MAX >> 2)
#define BASE1      10
#define BASE2      1000000000   // BASE1 ** (BASE1 - 1)
#define subBASE2   999999999    // subBASE2 == BASE2 - 1
#define overBASE2  0xc0000000   // overBASE2 > subBASE2


#if (BASE2 >= MAX_UNIT_VALUE)
#error Compilation Error-1 : (BASE2 >= MAX_UNIT_VALUE)
#endif

#if (!(BASE1 * (BASE2/BASE1 + 1) < MAX_UNIT_VALUE))
#error Compilation Error-2 : (!(BASE1 * (BASE2/BASE1 + 1) < MAX_UNIT_VALUE))
#endif

#if (BASE2 != (subBASE2 + 1))
#error Compilation Error-3 : (BASE2 != (subBASE2 + 1))
#endif

#if (!(overBASE2 > subBASE2))
#error Compilation Error-4 : (!(overBASE2 > subBASE2))
#endif

const ulong ULONG_MSB = static_cast<ulong>(1) << (sizeof(ulong) * CHAR_BIT - 1);



#define ROSSI_TEST_BINARY_OP(testcase_id, op) \
	{ \
	  RossiBigInt z(0); \
	  z = vtest[testcase_id].first op vtest[testcase_id].second; \
	  cout << vtest[testcase_id].first.getstr_hex_value() \
	       << " " \
	       << #op \
	       << " " \
               << vtest[testcase_id].second.getstr_hex_value() \
	       << " = " \
	       << z.getstr_hex_value() \
	       << endl; \
	}


#define VIN_TEST_BINARY_OP_BIG(testcase_id, op) \
	{ \
	  VinBigInt z(0); \
	  z = vtest[testcase_id].first op vtest[testcase_id].second; \
	  cout << vtest[testcase_id].first \
	       << " " \
	       << #op \
	       << " " \
               << vtest[testcase_id].second \
	       << " = " \
	       << z \
	       << endl; \
	}


#define VIN_TEST_BINARY_OP_ULONG(testcase_id, op) \
	{ \
	  VinBigInt z(0); \
	  z = vtest[testcase_id].first op vtest[testcase_id].second; \
	  cout << vtest[testcase_id].first \
	       << " " \
	       << #op \
	       << " " \
               << vtest[testcase_id].second \
	       << " = " \
	       << z \
	       << endl; \
	}


#define ROSSI_TEST_BINARY_WITH_LESS_OP(testcase_id, op) \
	{ \
	  RossiBigInt z(0); \
	  if (!(vtest[testcase_id].first < vtest[testcase_id].second)) \
	  { \
	  z = vtest[testcase_id].first op vtest[testcase_id].second; \
	  cout << vtest[testcase_id].first.getstr_hex_value() \
	       << " " \
	       << #op \
	       << " " \
               << vtest[testcase_id].second.getstr_hex_value() \
	       << " = " \
	       << z.getstr_hex_value() \
	       << endl; \
	  } \
	}
	
#define ROSSI_TEST_UNARY_WITH_LESS_OP(testcase_id, op) \
	{ \
	  if (!(vtest[testcase_id].first < vtest[testcase_id].second)) \
	  { \
	  cout << vtest[testcase_id].first.getstr_hex_value(); \
	  vtest[testcase_id].first op vtest[testcase_id].second; \
	  cout << "" \
	       << " " \
	       << #op \
	       << " " \
         << vtest[testcase_id].second.getstr_hex_value() \
	       << " = " \
	       << vtest[testcase_id].first.getstr_hex_value() \
	       << endl; \
	  } \
	}
	


#define ROSSI_TEST_BOOLEAN_OP(testcase_id, op) \
	{ \
	  bool z; \
	  z = vtest[testcase_id].first op vtest[testcase_id].second; \
	  cout << vtest[testcase_id].first.getstr_hex_value() \
	       << " " \
	       << #op \
	       << " " \
               << vtest[testcase_id].second.getstr_hex_value() \
	       << " : " \
	       << (z ? "TRUE" : "FALSE") \
	       << endl; \
	}


#define ROSSI_CREATE_EMPTY_VTEST vector<pair<RossiBigInt, RossiBigInt> > vtest
#define VIN_CREATE_EMPTY_VTEST_BIG_BIG vector<pair<VinBigInt, VinBigInt> > vtest
#define VIN_CREATE_EMPTY_VTEST_BIG_ULONG vector<pair<VinBigInt, ulong> > vtest

#define ROSSI_ADD_TEST_CASE_ULONG(a, b) \
	  vtest.push_back(pair<RossiBigInt, RossiBigInt> (RossiBigInt(a), RossiBigInt(b)))

#define ROSSI_ADD_TEST_CASE_STRING_DEC(a, b) \
	  vtest.push_back(pair<RossiBigInt, RossiBigInt> (RossiBigInt(a, DEC_DIGIT), RossiBigInt(b, DEC_DIGIT)))

#define ROSSI_ADD_TEST_CASE_STRING_HEX(a, b) \
	  vtest.push_back(pair<RossiBigInt, RossiBigInt> (RossiBigInt(a, HEX_DIGIT), RossiBigInt(b, HEX_DIGIT)))


#define VIN_ADD_TEST_CASE_ULONG_for_BIG_BIG(a, b) \
	  vtest.push_back(pair<VinBigInt, VinBigInt> (VinBigInt(a), VinBigInt(b)))

#define VIN_ADD_TEST_CASE_STRING_DEC_for_BIG_BIG(a, b) \
	  vtest.push_back(pair<VinBigInt, VinBigInt> (VinBigInt(a, DEC_DIGIT), VinBigInt(b, DEC_DIGIT)))

#define VIN_ADD_TEST_CASE_STRING_HEX_for_BIG_BIG(a, b) \
	  vtest.push_back(pair<VinBigInt, VinBigInt> (VinBigInt(a, HEX_DIGIT), VinBigInt(b, HEX_DIGIT)))


#define VIN_ADD_TEST_CASE_ULONG_for_BIG_ULONG(a, b) \
	  vtest.push_back(pair<VinBigInt, ulong> (VinBigInt(a), b))

#define VIN_ADD_TEST_CASE_STRING_DEC_for_BIG_ULONG(a, b) \
	  vtest.push_back(pair<VinBigInt, ulong> (VinBigInt(a, DEC_DIGIT), b)))

#define VIN_ADD_TEST_CASE_STRING_HEX_for_BIG_ULONG(a, b) \
	  vtest.push_back(pair<VinBigInt, ulong> (VinBigInt(a, HEX_DIGIT), b))



////////////
// FUNCTIONS
////////////
void ShowVersion()
{
  cerr << endl;
  cerr << "BigInt - C++ class for computation with arbitrary large integers" << endl;
  cerr << "Version " << BIG_INT_VERSION_No << endl;
  cerr << "Compiled in " << (sizeof(ulong) * CHAR_BIT) << "-bit mode" << endl;

  cerr << endl;
  cerr << "Copyright (C) 1995       William A. Rossi - Class RossiBigInt" << endl;
  cerr << "Copyright (C) 1999-2009  Alex Vinokur - Class VinBigInt, Upgrading class RossiBigInt" << endl;

  cerr << endl;
  cerr << "This is free software; see the source for copying conditions." << endl;
  cerr << "There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << endl;
  cerr << endl;
}


////////////
// CONSTANTS
////////////
static const RossiBigInt Zero (0);
static const RossiBigInt One  (1);
static const RossiBigInt Two  (2);

static const ulong hex_digit_size_cns (4);
static const ulong digits_in_ulong_s ((sizeof (ulong) * CHAR_BIT)/hex_digit_size_cns);

///////////////
// STATIC INIT
///////////////

class Aux1
{
  private:
    map<char, ulong> hex_to_dec_digits_convertor_;

  public:
    Aux1 ()
    {
      hex_to_dec_digits_convertor_ ['0'] = 0;
      hex_to_dec_digits_convertor_ ['1'] = 1;
      hex_to_dec_digits_convertor_ ['2'] = 2;
      hex_to_dec_digits_convertor_ ['3'] = 3;
      hex_to_dec_digits_convertor_ ['4'] = 4;
      hex_to_dec_digits_convertor_ ['5'] = 5;
      hex_to_dec_digits_convertor_ ['6'] = 6;
      hex_to_dec_digits_convertor_ ['7'] = 7;
      hex_to_dec_digits_convertor_ ['8'] = 8;
      hex_to_dec_digits_convertor_ ['9'] = 9;
      hex_to_dec_digits_convertor_ ['a'] = 10;
      hex_to_dec_digits_convertor_ ['A'] = 10;
      hex_to_dec_digits_convertor_ ['b'] = 11;
      hex_to_dec_digits_convertor_ ['B'] = 11;
      hex_to_dec_digits_convertor_ ['c'] = 12;
      hex_to_dec_digits_convertor_ ['C'] = 12;
      hex_to_dec_digits_convertor_ ['d'] = 13;
      hex_to_dec_digits_convertor_ ['D'] = 13;
      hex_to_dec_digits_convertor_ ['e'] = 14;
      hex_to_dec_digits_convertor_ ['E'] = 14;
      hex_to_dec_digits_convertor_ ['f'] = 15;
      hex_to_dec_digits_convertor_ ['F'] = 15;
    }

    map<char, ulong> get_hex_to_dec_digits_convertor ()
    {
      return hex_to_dec_digits_convertor_;
    }

};

Aux1 aux1_ins;

map<char, ulong> BaseBigInt::hex_to_dec_digits_convertor_s (aux1_ins.get_hex_to_dec_digits_convertor());





//////////////
// DEFINITIONS
//////////////


// ================
// class BaseBigInt
// ================

// ------------------
bool BaseBigInt::is_empty() const
{
  return units_.empty();
}


// ------------------
ulong BaseBigInt::get_units_size() const
{
  return units_.size();
}



// ------------------
BaseBigInt::~BaseBigInt()
{
}



// ===============
// class VinBigInt
// ===============

// ------------------
static ulong carry_s = 0;
ulong add_units(ulong n1, ulong n2)
{
  n1 += (n2 + carry_s);
  carry_s = (overBASE2 & n1) || (n1 > subBASE2);
  return (carry_s ? (n1 - BASE2) : n1);
}



// ------------------
// Constructor-0
VinBigInt::VinBigInt () 
{
}


// ------------------
// Constructor-1
VinBigInt::VinBigInt (ulong unit_i) 
{
  if (!(unit_i < BASE2))
  {
    FATAL_ERROR ("ulong value too big");
    cerr << "unit_i         = " << dec << unit_i << ", Ox" << hex << unit_i << endl;
    cerr << "BASE2          = " << dec << BASE2 << ", Ox" << hex << BASE2 << endl;
    cerr << "MAX_UNIT_VALUE = " << dec << MAX_UNIT_VALUE << ", Ox" << hex << MAX_UNIT_VALUE << endl;
    cerr << endl;
  }
  ASSERTION (unit_i < BASE2);
  units_.reserve(units_.size() + 1);
  units_.push_back (unit_i);
}



// ------------------
// Constructor-2
VinBigInt::VinBigInt (const string& arg_i, ulong digit_base_i)
{
bool rc = init_via_string (arg_i, digit_base_i);
  ASSERTION (rc);
}

// ------------------
// Constructor-3
VinBigInt::VinBigInt (const RossiBigInt& arg_i)
{
const string str (arg_i.getstr_pure_hex_value ());
bool rc = init_via_string (str, HEX_DIGIT);
  ASSERTION (rc);
}



// ------------------
ulong VinBigInt::get_pure_ulong () const
{
  ASSERTION (!units_.empty());
  if (units_.size() > 1)
  {
    FATAL_ERROR ("ulong can't be obtained: units_.size() too big");
    cerr << "units_.size() = " << units_.size() << endl;
    cerr << "units_.size() must be = 1" << endl;
    ASSERTION (units_.size() == 1);
  }
  ASSERTION (units_.size() == 1);
  return units_.front();
}

// ------------------
// VinBigInt::operator ulong () const
// {
//  return get_pure_ulong();
// }


// ------------------
bool VinBigInt::init_via_string (const string& arg_i, ulong digit_base_i)
{
  ASSERTION (units_.empty());
  ASSERTION ((digit_base_i ==  16) || (digit_base_i ==  10));

  units_.push_back(0);

  for (ulong i = 0; i < arg_i.size(); i++)
  {
    switch (digit_base_i)
    {
      case DEC_DIGIT:
        if (!isdigit (arg_i[i])) 
        {
          FATAL_ERROR ("string contains non-decimal digit");
          cerr << "string = " << arg_i << endl;
          cerr << i << "-th char = " << arg_i[i] << endl;
          ASSERTION (0);
          return false; // unused
        }
        break;

      case HEX_DIGIT:
        if (!isxdigit (arg_i[i])) 
        {
          FATAL_ERROR ("string contains non-hexadecimal digit");
          cerr << "string = " << arg_i << endl;
          cerr << i << "-th char = " << arg_i[i] << endl;
          ASSERTION (0);
          return false; // unused
        }
        break;

      default:
        ASSERTION (0);
        return false;
        break; // unused

    }
  }

  for (ulong i = 0; i < arg_i.size(); i++)
  {
    *this = (*this) * digit_base_i
          + VinBigInt (hex_to_dec_digits_convertor_s[arg_i[i]]);
  }
  return true;
}

// ------------------
VinBigInt VinBigInt::operator+ (const VinBigInt& arg_i) const
{
VinBigInt ret;
const ulong max_size (MAX_VAL (units_.size (), arg_i.units_.size ()));

vector<ulong> u1 (units_);
vector<ulong> u2 (arg_i.units_);

  u1.reserve(max_size);
  u2.reserve(max_size);
  ret.units_.reserve(max_size + 1);

  u1.resize(max_size);
  u2.resize(max_size);
  ret.units_.resize(max_size);

  carry_s = 0;
  transform (&u1[0], &u1[0] + max_size, &u2[0], &ret.units_[0], add_units);

  if (carry_s) ret.units_.push_back (carry_s);

  return ret;

}


// ------------------
VinBigInt VinBigInt::operator* (ulong arg_i) const
{
VinBigInt ret (0);
  for (ulong i = 0; i < arg_i; i++) ret = ret + (*this);
  return ret;
}


// ------------------
bool VinBigInt::operator< (const VinBigInt& arg_i) const
{
  if (units_.size() < arg_i.units_.size()) return true;
  if (arg_i.units_.size() < units_.size()) return false;

  ASSERTION (units_.size() == arg_i.units_.size());
  for (ulong i = (units_.size() - 1); i > 0; i--)
  {
    if (units_[i] < arg_i.units_[i]) return true;
    if (arg_i.units_[i] < units_[i]) return false;
  }
  return (units_[0] < arg_i.units_[0]);
}


// ------------------
bool VinBigInt::operator<= (const VinBigInt& arg_i) const
{
  if (*this < arg_i) return true;
  if (*this == arg_i) return true;
  return false;
}



// ------------------
bool VinBigInt::operator> (const VinBigInt& arg_i) const
{
  return (!(*this <= arg_i));
}


// ------------------
bool VinBigInt::operator>= (const VinBigInt& arg_i) const
{
  return (!(*this < arg_i));
}

// ------------------
bool VinBigInt::operator== (const VinBigInt& arg_i) const
{
  if (*this < arg_i) return false;
  if (arg_i < *this) return false;
  return true;
}

// ------------------
bool VinBigInt::operator!= (const VinBigInt& arg_i) const
{
  return (!(*this == arg_i));
}


// ------------------
ostream& operator<< (ostream& os, const VinBigInt& ins_i)
{
  // ASSERTION (!ins_i.units_.empty ());
  if (ins_i.is_empty ()) return os << "is_empty";

  for (ulong i = (ins_i.units_.size () - 1); i; --i) 
  {
    os << ins_i.units_ [i] << setw (BASE1 - 1) << setfill ('0');
  }
  return os << ins_i.units_ [0];
}




// ------------------
void VinBigInt::All_Tests()
{
  Test100_Operator_Add_Bigint();
  Test300_Operator_Multiplication_Ulong ();
}



// ------------------
void VinBigInt::Test100_Operator_Add_Bigint()
{
ostringstream oss;
  oss << "VinBigInt::Test100_Operator_Add_Bigint" << endl;

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  VIN_CREATE_EMPTY_VTEST_BIG_BIG;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (0);
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (999999998);
  ulong_nums.push_back (999999999);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      VIN_ADD_TEST_CASE_ULONG_for_BIG_BIG (ulong_nums[i], ulong_nums[k]);
    }
  }


  // --- hexstr_nums ---
  hexstr_nums.push_back ("0");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");


  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      VIN_ADD_TEST_CASE_STRING_HEX_for_BIG_BIG (hexstr_nums[i], hexstr_nums[k]);
    }
  }


  for (ulong i = 0; i < vtest.size(); i++)
  {
    VIN_TEST_BINARY_OP_BIG(i, +);
  }

}



// ------------------
void VinBigInt::Test300_Operator_Multiplication_Ulong()
{
ostringstream oss;
  oss << "VinBigInt::Test300_Operator_Multiplication_Ulong";

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  VIN_CREATE_EMPTY_VTEST_BIG_ULONG;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (0);
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0x10);
  ulong_nums.push_back (0x100);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      VIN_ADD_TEST_CASE_ULONG_for_BIG_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }


  // --- hexstr_nums ---
  hexstr_nums.push_back ("0");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");


  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      VIN_ADD_TEST_CASE_STRING_HEX_for_BIG_ULONG (hexstr_nums[i], ulong_nums[k]);
    }
  }


  for (ulong i = 0; i < vtest.size(); i++)
  {
    VIN_TEST_BINARY_OP_ULONG(i, *);
  }

}


// =================
// class RossiBigInt
// =================


// ------------------
// Constructor-0
RossiBigInt::RossiBigInt () 
{
  ASSERTION(is_empty());
}


// ------------------
// Constructor-1
RossiBigInt::RossiBigInt (ulong unit_i) 
{
  ASSERTION (units_.empty());
  units_.push_back (unit_i);
}


// ------------------
// Constructor-2
RossiBigInt::RossiBigInt (const string& arg_i, ulong digit_base_i) 
{
const bool rc = init_via_string (arg_i, digit_base_i);
  ASSERTION (rc);
}



// ------------------
// Constructor-3
RossiBigInt::RossiBigInt (const VinBigInt& arg_i)
{
ostringstream oss;
  oss << arg_i;
const string str (oss.str());
bool rc = init_via_string (str, DEC_DIGIT);
  ASSERTION (rc);
}


// ------------------
ulong RossiBigInt::get_pure_ulong () const
{
  ASSERTION (!units_.empty());
  if (units_.size() > 1)
  {
    FATAL_ERROR ("ulong can't be obtained: units_.size() too big");
    cerr << "units_.size() = " << units_.size() << endl;
    cerr << "Hex value = " << getstr_hex_value() << endl;
    cerr << "units_.size() must be = 1" << endl;
    ASSERTION (units_.size() == 1);
  }
  ASSERTION (units_.size() == 1);
  return units_.front();
}

// ------------------
// RossiBigInt::operator ulong () const
// {
//  return get_pure_ulong();
// }


// ------------------
bool RossiBigInt::init_via_string (const string& arg_i, ulong digit_base_i)
{
  ASSERTION (units_.empty());
  ASSERTION ((digit_base_i ==  16) || (digit_base_i ==  10));

  units_.push_back(0);

  for (ulong i = 0; i < arg_i.size(); i++)
  {
    switch (digit_base_i)
    {
      case DEC_DIGIT:
        if (!isdigit (arg_i[i])) 
        {
          FATAL_ERROR ("string contains non-decimal digit");
          cerr << "string = " << arg_i << endl;
          cerr << i << "-th char = " << arg_i[i] << endl;
          ASSERTION (0);
          return false; // unused
        }
        break;

      case HEX_DIGIT:
        if (!isxdigit (arg_i[i])) 
        {
          FATAL_ERROR ("string contains non-hexadecimal digit");
          cerr << "string = " << arg_i << endl;
          cerr << i << "-th char = " << arg_i[i] << endl;
          ASSERTION (0);
          return false; // unused
        }
        break;

      default:
        ASSERTION (0);
        return false;
        break; // unused

    }
  }

  for (ulong i = 0; i < arg_i.size(); i++)
  {
    *this = (*this) * digit_base_i;
   	*this = (*this) + RossiBigInt (hex_to_dec_digits_convertor_s[arg_i[i]]);
  }
  return true;
}


// ------------------
void RossiBigInt::resize_units(ulong size_i)
{
  units_.resize(size_i);
}

// ------------------
void RossiBigInt::truncate_units()
{
  while ((units_.size() > 1) && (units_.back() == 0))
  {
    units_.pop_back();
  }
  ASSERTION(!is_empty());

}

// ------------------
bool RossiBigInt::units_not_front_back_is_null () const
{
  ASSERTION (!units_.empty());
  if (units_.size() == 1) return false;
  return (units_.back() == 0);
}



// ------------------
// RossiBigInt& RossiBigInt::operator= (ulong arg_i)
// {
//  *this = RossiBigInt (arg_i);
//  return *this;
// }

// ------------------
RossiBigInt RossiBigInt::operator+ (const RossiBigInt& arg_i)
{
RossiBigInt ret (0);
RossiBigInt arg (arg_i);
ulong carry = 0;

const ulong max_size (MAX_VAL (get_units_size(), arg.get_units_size()));

  resize_units (max_size + 1);
  arg.resize_units (max_size + 1);
  ret.resize_units (max_size + 1);

	for (ulong i = 0; i < units_.size(); i++)
  {
  	 
    ret.units_[i] = units_[i] + arg.units_[i] + carry;
    if (carry == 0)
    {
      carry = ((ret.units_[i] < units_[i] || ret.units_[i] < arg.units_[i]) ? 1 : 0);
    }
    else
    {
      carry = ((ret.units_[i] <= units_[i] || ret.units_[i] <= arg.units_[i]) ? 1 : 0);
    }
  }

  if (units_not_front_back_is_null ())
  { 
  	truncate_units ();
  }
  
  if (ret.units_not_front_back_is_null ())
  { 
  	ret.truncate_units ();
  }

  return ret;

}

// ------------------
RossiBigInt RossiBigInt::operator+ (ulong arg_i)
{
  return (*this + RossiBigInt (arg_i));
}


// ------------------
bool RossiBigInt::operator< (const RossiBigInt& arg_i) const
{
  if (units_.size() < arg_i.units_.size()) return true;
  if (arg_i.units_.size() < units_.size()) return false;

  ASSERTION (units_.size() == arg_i.units_.size());
  for (ulong i = (units_.size() - 1); i > 0; i--)
  {
    if (units_[i] < arg_i.units_[i]) return true;
    if (arg_i.units_[i] < units_[i]) return false;
  }
  return (units_[0] < arg_i.units_[0]);
}


// ------------------
bool RossiBigInt::operator<= (const RossiBigInt& arg_i) const
{
  if (*this < arg_i) return true;
  if (*this == arg_i) return true;
  return false;
}



// ------------------
bool RossiBigInt::operator> (const RossiBigInt& arg_i) const
{
  return (!(*this <= arg_i));
}


// ------------------
bool RossiBigInt::operator>= (const RossiBigInt& arg_i) const
{
  return (!(*this < arg_i));
}

// ------------------
bool RossiBigInt::operator== (const RossiBigInt& arg_i) const
{
  if (*this < arg_i) return false;
  if (arg_i < *this) return false;
  return true;
}


// ------------------
bool RossiBigInt::operator!= (const RossiBigInt& arg_i) const
{
  return (!(*this == arg_i));
}



// ------------------
RossiBigInt RossiBigInt::operator/ (const RossiBigInt& arg_i) const
{
  return Divide(*this, arg_i, NULL);
}


// ------------------
RossiBigInt RossiBigInt::operator% (const RossiBigInt& arg_i) const
{
RossiBigInt ret;
  Divide(*this, arg_i, &ret);
  return ret;
}



// ------------------
RossiBigInt RossiBigInt::operator>> (ulong shift_i)
{
RossiBigInt tmp;
RossiBigInt ret;

  tmp = *this;

  ret.resize_units (units_.size());

  ASSERTION (ret.get_units_size() == tmp.get_units_size());

  for (ulong i = 0; i < shift_i; i++)
  {
    ret.units_.back() = (tmp.units_.back() >> 1);

    for (long j = (tmp.units_.size() - 1); j >= 0; j--)   // j must be of signed type
    {
      ret.units_[j] = (tmp.units_[j] >> 1);

      if ((tmp.units_[j + 1] & 1) != 0)
      {
        ret.units_[j] |= ULONG_MSB;      // Set MSB bit
      }
    }
    tmp = ret;
  }

  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();

  return ret;
}


// ------------------
RossiBigInt RossiBigInt::operator<< (ulong shift_i)
{
RossiBigInt tmp;
RossiBigInt ret;

  tmp = *this;

  ret.resize_units (units_.size() + 1);

  ASSERTION ((ret.get_units_size() + 1) == tmp.get_units_size());

  for (ulong i = 0; i < shift_i; i++)
  {
    ret.units_.front() = (tmp.units_.front() << 1);
    for (ulong j = 1; j < tmp.units_.size(); j++)
    {
      ret.units_[j] = (tmp.units_[j] << 1);
      if ((tmp.units_[j-1] & ULONG_MSB) != 0)
      {
        ret.units_[j] |= 1;     // Set MSB bit
      }
    }
    if ((tmp.units_.back() & ULONG_MSB) != 0)
    {
      ret.units_.back() |= 1;   // Set MSB bit
    }
    tmp = ret;
  }

  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();

  return ret;
}



// ------------------
RossiBigInt& RossiBigInt::operator>>= (ulong shift_i)
{
ulong carry;
  units_.push_back(0);

  for (ulong i = 0; i < shift_i; i++)
  {
    carry = units_.back() & 1;
    units_.back() >>= 1;

    for (long j = (units_.size() - 1); j>=0; j--)   // j must be of signed type
    {
      if (carry)
      {
        carry = units_[j] & 1;
        units_[j] >>= 1;
        units_[j] |= ULONG_MSB;
      }
      else
      {
        carry = units_[j] & 1;
        units_[j] >>= 1;
      }
    }
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;
}



// ------------------
RossiBigInt& RossiBigInt::operator<<= (ulong shift_i)
{
ulong carry;

const ulong push_back_size (shift_i/(sizeof (ulong) * CHAR_BIT) + 1);

  for (ulong i = 0; i < (push_back_size + 1); i++)
  {
    units_.push_back(0);
  }

  for (ulong i = 0; i < shift_i; i++)
  {

    carry = units_.front() & ULONG_MSB;
    units_.front() <<= 1;

    for (ulong j = 1; j < units_.size(); j++)
    {
      if (carry)
      {
        carry = units_[j] & ULONG_MSB;
        units_[j] <<= 1;
        units_[j] |= 1;
      }
      else
      {
        carry = units_[j] & ULONG_MSB;
        units_[j] <<= 1;
      }
    }
  }

  if (units_not_front_back_is_null ()) truncate_units ();
  return *this;
}



// ------------------
RossiBigInt& RossiBigInt::operator+=(const RossiBigInt& arg_i)
{
ulong carry = 0;
ulong prevdigit;
RossiBigInt arg (arg_i);

const ulong max_size (MAX_VAL (get_units_size(), arg.get_units_size()));

  resize_units (max_size + 1);
  arg.resize_units (max_size + 1);

  for (ulong i = 0; i < units_.size(); i++)
  {
    prevdigit = units_[i];
    units_[i] = units_[i] + arg.units_[i] + carry;
    if (carry == 0)
    {
      carry = ((units_[i] < prevdigit || units_[i] < arg.units_[i]) ? 1 : 0);
    }
    else
    {
      carry = ((units_[i] <= prevdigit || units_[i] <= arg.units_[i]) ? 1 : 0);
    }
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;
}


// ------------------
RossiBigInt& RossiBigInt::operator++()  // Pre Increment operator -- faster than add
{
  units_.push_back(0);

  units_.front()++;
  for (ulong i = 1; i < units_.size(); i++)
  {
    if (units_[i-1]) break;
    units_[i]++;
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;
}


// ------------------
RossiBigInt RossiBigInt::operator++ (int)  // Post Increment operator -- faster than add
{
RossiBigInt tmp (*this);
  ++*this;
  return tmp;
}




// ------------------
RossiBigInt RossiBigInt::operator- ()  // Negates a number
{
RossiBigInt ret;
  ret.resize_units(units_.size() + 1);

  for (ulong i = 0; i < units_.size(); i++)
  {
    ret.units_[i] = ~units_[i];
  }

  ret = ret + One;

  if (units_not_front_back_is_null ()) truncate_units ();

  return ret;
}



// ------------------
RossiBigInt RossiBigInt::operator-(const RossiBigInt& arg_i)
{
RossiBigInt ret (Zero);
RossiBigInt arg (arg_i);
ulong borrow = 0;

const ulong max_size (MAX_VAL (get_units_size(), arg.get_units_size()));

  resize_units (max_size + 1);
  arg.resize_units (max_size + 1);
  ret.resize_units (max_size + 1);

  if (*this < arg)
  {
    FATAL_ERROR ("minuend < subtracter");
    cerr << "minuend    = " << this->getstr_hex_value() << endl;
    cerr << "subtracter = " << arg.getstr_hex_value() << endl;
    ASSERTION (0);
  }

  for (ulong i = 0; i < units_.size(); i++)
  {
    ret.units_[i] = units_[i] - arg.units_[i] - borrow;
    
    if (borrow == 0)
    {
      borrow = ((units_[i] < arg.units_[i]) ? 1 : 0);
    }
    else
    {
      borrow = ((units_[i] <= arg.units_[i]) ? 1 : 0);
    }
  }

  if (units_not_front_back_is_null ()) truncate_units ();
  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();

  return ret;
}


// ------------------
RossiBigInt& RossiBigInt::operator-= (const RossiBigInt& arg_i)
{
ulong borrow = 0;
RossiBigInt arg (arg_i);
ulong prevdigit;

const ulong max_size (MAX_VAL (get_units_size(), arg.get_units_size()));
	resize_units (max_size + 1);
  arg.resize_units (max_size + 1);
  
  if (*this < arg)
  {
    FATAL_ERROR ("minuend < subtracter");
    cerr << "minuend    = " << this->getstr_hex_value() << endl;
    cerr << "subtracter = " << arg.getstr_hex_value() << endl;
    ASSERTION (0);
  }

  for (ulong i = 0; i < units_.size(); i++)
  {
    prevdigit = units_[i];
    units_[i] = units_[i] - arg.units_[i] - borrow;

    if (borrow == 0)
    {
      borrow = ((prevdigit < arg.units_[i]) ? 1 : 0);
    }
    else
    {
      borrow = ((prevdigit <= arg.units_[i]) ? 1 : 0);
    }
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;
}




// ------------------
RossiBigInt& RossiBigInt::operator--()  // Pre Decrement operator -- faster than add
{
  units_.front()--;
  for (ulong i = 1; i < units_.size(); i++)
  {
    if (units_[i-1] != ULONG_MAX) break;
    ASSERTION (units_[i-1] < ULONG_MAX);

    units_[i]--;
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;
}


// ------------------
RossiBigInt RossiBigInt::operator-- (int)  // Post Decrement operator -- faster than add
{
  RossiBigInt tmp (*this);
  --*this;
  return tmp;
}



// ------------------
RossiBigInt RossiBigInt::operator& (const RossiBigInt& arg_i)
{
const ulong max_size (MAX_VAL (get_units_size (), arg_i.get_units_size ()));

RossiBigInt ret;
RossiBigInt arg (arg_i);

  ret.resize_units(max_size);
  arg.resize_units(max_size);
  resize_units(max_size);

  for (long i = (units_.size() - 1); i>=0; i--)   // i must be of signed type
  {
    ret.units_[i] = units_[i] & arg.units_[i];
  }

  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();
  if (units_not_front_back_is_null ()) truncate_units ();

  return ret;
}


// ------------------
RossiBigInt RossiBigInt::operator| (const RossiBigInt& arg_i)
{
const ulong max_size (MAX_VAL (get_units_size (), arg_i.get_units_size ()));

RossiBigInt ret;
RossiBigInt arg (arg_i);

  ret.resize_units(max_size);
  arg.resize_units(max_size);
  resize_units(max_size);

  for (long i = (units_.size() - 1); i>=0; i--)   // i must be of signed type
  {
    ret.units_[i] = units_[i] | arg.units_[i];
  }

  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();
  if (units_not_front_back_is_null ()) truncate_units ();

  return ret;
}



// ------------------
RossiBigInt RossiBigInt::operator^ (const RossiBigInt& arg_i)
{
const ulong max_size (MAX_VAL (get_units_size (), arg_i.get_units_size ()));

RossiBigInt ret;
RossiBigInt arg (arg_i);

  ret.resize_units(max_size);
  arg.resize_units(max_size);
  resize_units(max_size);

  for (long i = (units_.size() - 1); i>=0; i--)   // i must be of signed type
  {
    ret.units_[i] = units_[i] ^ arg.units_[i];
  }

  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();
  if (units_not_front_back_is_null ()) truncate_units ();

  return ret;

}


// ------------------
RossiBigInt RossiBigInt::operator~ ()
{
RossiBigInt ret;

  ret.resize_units(get_units_size());

  for (long i = (units_.size() - 1); i>=0; i--)   // i must be of signed type
  {
    ret.units_[i] = ~units_[i];
  }

  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();

  return ret;

}



// ------------------
RossiBigInt& RossiBigInt::operator&= (const RossiBigInt& arg_i)
{
const ulong max_size (MAX_VAL (get_units_size (), arg_i.get_units_size ()));

RossiBigInt arg (arg_i);

  arg.resize_units(max_size);
  resize_units(max_size);

  for (long i = (units_.size() - 1); i>=0; i--)   // i must be of signed type
  {
    units_[i] = units_[i] & arg.units_[i];
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;

}


// ------------------
RossiBigInt& RossiBigInt::operator|=(const RossiBigInt& arg_i)
{
const ulong max_size (MAX_VAL (get_units_size (), arg_i.get_units_size ()));

RossiBigInt arg (arg_i);

  arg.resize_units(max_size);
  resize_units(max_size);

  for (long i = (units_.size() - 1); i>=0; i--)   // i must be of signed type
  {
    units_[i] = units_[i] | arg.units_[i];
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;

}


// ------------------
RossiBigInt& RossiBigInt::operator^=(const RossiBigInt& arg_i)
{
const ulong max_size (MAX_VAL (get_units_size (), arg_i.get_units_size ()));

RossiBigInt arg (arg_i);

  arg.resize_units(max_size);
  resize_units(max_size);

  for (long i = (units_.size() - 1); i>=0; i--)   // i must be of signed type
  {
    units_[i] = units_[i] ^ arg.units_[i];
  }

  if (units_not_front_back_is_null ()) truncate_units ();

  return *this;

}




// ------------------
RossiBigInt RossiBigInt::operator* (RossiBigInt arg_i) const
{
RossiBigInt tmp;
RossiBigInt ret;

 
  tmp = *this;
  ret = Zero;
  // ret.resize_units (get_units_size () + arg_i.get_units_size ());
  
  do
  {
  
  	
    if ((arg_i.units_.front() & 1) != 0) ret += tmp;
    arg_i >>= 1;
    tmp <<= 1;
  } while (arg_i != Zero);

  if (ret.units_not_front_back_is_null ()) ret.truncate_units ();

  return ret;
}


// ------------------
RossiBigInt RossiBigInt::operator* (ulong arg_i) const
{
  return ((*this) * RossiBigInt (arg_i));
}

				 

// ------------------
RossiBigInt RossiBigInt::Divide (
		const RossiBigInt& dividend_i, 
		const RossiBigInt& divisor_i, 
		RossiBigInt *remainder_o
		) const
{
RossiBigInt dividend (dividend_i); 
RossiBigInt divisor (divisor_i); 

long shiftcnt (0);

  // --- Check for attempt to divide by zero ---


  if (divisor == Zero)
  {
    FATAL_ERROR ("divisor == Zero");
    ASSERTION (0 && "divisor == Zero");

    shiftcnt = 1 / shiftcnt;  // Force a divide by zero exception. (shiftcnt=0)
  }

RossiBigInt quotient (Zero);

  quotient.resize_units (dividend.get_units_size ());

  if (remainder_o != NULL)
  {
    remainder_o->resize_units (dividend.get_units_size ());
  }


  // --- Left shift divisor until it is greater than or equal to dividend ---
  // while ( divisor < dividend && ((divisor.units_.back() & ULONG_MSB) == 0))
  while ( divisor < dividend)
  { 	
    divisor <<= 1;
    shiftcnt++;
  }

  if (divisor > dividend)      // If divisor is greater than dividend, right shift divisor
  {
    divisor >>= 1;
    shiftcnt--;   
  }

  if (shiftcnt >= 0)
  { 	
    for(long i = 0; i <= shiftcnt; i++)
    {    	
      if ( divisor <= dividend)  // If divisor is greater than dividend, then the bit is a 1 
      {       	
        dividend -= divisor;     // Subtract divisor from dividend 
        divisor  >>= 1;          // Right shift divisor 
        quotient <<= 1;          // Left shift quotient
        quotient++;              // Increment quotient           // Increment quotient 
      }
      else
      {      	
        divisor >>= 1;             // Bit is 0, right shift divisor, left shift quotient
        quotient <<= 1;
      }
    }
  }

RossiBigInt remainder (dividend); 
  if (remainder.units_not_front_back_is_null ())
	{ 
  	remainder.truncate_units ();
  }	

  if (remainder_o != NULL) 
  {
    *remainder_o = remainder;
    if (remainder_o->units_not_front_back_is_null ()) 
		{
    	remainder_o->truncate_units ();
    }
  }

  if (quotient.units_not_front_back_is_null ()) 
	{
  	quotient.truncate_units ();
  }

  ASSERTION ((quotient * divisor_i + remainder) == dividend_i);
  return quotient;
}



// ------------------
RossiBigInt RossiBigInt::sqrt()		// Returns the square root of this
{
RossiBigInt ret;
RossiBigInt tmp;
RossiBigInt delta;

RossiBigInt mask (Two);

  tmp = *this;
  mask = -mask;

ulong i = 0;
  ret = tmp; 
  for (i = 0; ret != Zero; ret >>= 1, i++)
  {
    // Do nothing
  }

  ret = tmp; 
  for (ulong j = 0; j < ulong(i >> 1); ret >>= 1, j++)
  {
    // Do nothing
  }

  do
  {
    // -----------------------------------------------
    // We are really performing the fuction:
    //	 delta = (tmp/ret - ret) / 2;
    //   below, but since these are unsigned numbers,
    //   we MUST do the subtraction last in order for
    //   the ret = ret + delta;  equation to work properly.
    // -----------------------------------------------

    delta = ( tmp >> ulong(1)) / ret - (ret >> ulong(1));
    ret = ret + delta;
  } while ((delta &= mask) != Zero);

  return ret;
}


// ------------------
void RossiBigInt::dbg_show () const
{
  cout << "--- BEGIN ---" << endl;
  for (ulong i = 0; i < units_.size(); i++)
  {
    cout << "units_[" << i << "] = 0x" << hex << units_[i] << endl;
  }
  cout << "---- END ----" << endl;
}



// ------------------
string RossiBigInt::getstr_pure_hex_value () const
{
const std::size_t HEX_SETW = sizeof(ulong) * 2;
ostringstream oss;
  ASSERTION (!units_.empty ());
  // if (ins_i.is_empty ()) return oss << "is_empty";

  oss << hex;
  oss << units_.back();
  for (long i = (units_.size () - 2); i>= 0; i--) 
  {
    oss << setw (HEX_SETW) 
        << setfill ('0') 
        << units_ [i];
  }
  oss << dec;
  return oss.str();
}


// ------------------
string RossiBigInt::getstr_hex_value () const
{
ostringstream oss;
  oss << "0x";
  oss << getstr_pure_hex_value();
  return oss.str();
}




// ------------------
ostream& operator<< (ostream& os, const RossiBigInt& ins_i)
{
VinBigInt vin (ins_i.getstr_pure_hex_value(), HEX_DIGIT);

  return os << vin;
}



// ------------------
void RossiBigInt::Test100_Operator_Add_Bigint()
{
ostringstream oss;
  oss << "RossiBigInt::Test100_Operator_Add_Bigint" << endl;

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  ROSSI_CREATE_EMPTY_VTEST;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (0);
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0xFFFFFFFD);
  ulong_nums.push_back (0xFFFFFFFE);
  ulong_nums.push_back (0xFFFFFFFF);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }


  // --- hexstr_nums ---
  hexstr_nums.push_back ("0");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");


  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_STRING_HEX (hexstr_nums[i], hexstr_nums[k]);
    }
  }


  for (ulong i = 0; i < vtest.size(); i++)
  {
    ROSSI_TEST_BINARY_OP(i, +);
  }

}



// ------------------
void RossiBigInt::Test200_Operator_Subtraction_Bigint()
{
ostringstream oss;
  oss << "RossiBigInt::Test200_Operator_Subtraction_Bigint";

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  ROSSI_CREATE_EMPTY_VTEST;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (0);
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0xFFFFFFFD);
  ulong_nums.push_back (0xFFFFFFFE);
  ulong_nums.push_back (0xFFFFFFFF);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }


  // --- hexstr_nums ---
  hexstr_nums.push_back ("100000000");
  // hexstr_nums.push_back ("FFFFFFFF");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("0");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");

  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_STRING_HEX (hexstr_nums[i], hexstr_nums[k]);
    }
  }


  for (ulong i = 0; i < vtest.size(); i++)
  {
    // ROSSI_TEST_BINARY_OP(i, -);
    ROSSI_TEST_BINARY_WITH_LESS_OP(i, -);
  }

}



// ------------------
void RossiBigInt::Test210_Operator_Subtraction_Bigint()
{
ostringstream oss;
  oss << "RossiBigInt::Test210_Operator_Subtraction_Bigint";

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  ROSSI_CREATE_EMPTY_VTEST;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (0);
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0xFFFFFFFD);
  ulong_nums.push_back (0xFFFFFFFE);
  ulong_nums.push_back (0xFFFFFFFF);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }


  // --- hexstr_nums ---
  hexstr_nums.push_back ("100000000");
  // hexstr_nums.push_back ("FFFFFFFF");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("0");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");

  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_STRING_HEX (hexstr_nums[i], hexstr_nums[k]);
    }
  }


  for (ulong i = 0; i < vtest.size(); i++)
  {
    // ROSSI_TEST_BINARY_OP(i, -);
    ROSSI_TEST_UNARY_WITH_LESS_OP(i, -=);
  }

}






// ------------------
void RossiBigInt::Test300_Operator_Multiplication_Bigint()
{
ostringstream oss;
  oss << "RossiBigInt::Test300_Operator_Multiplication_Bigint";

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  ROSSI_CREATE_EMPTY_VTEST;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (0);
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0x10);
  ulong_nums.push_back (0x100);
  ulong_nums.push_back (0xFFFFFFFD);
  ulong_nums.push_back (0xFFFFFFFE);
  ulong_nums.push_back (0xFFFFFFFF);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }


  // --- hexstr_nums ---
  hexstr_nums.push_back ("0");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");


  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_STRING_HEX (hexstr_nums[i], hexstr_nums[k]);
    }
  }


  for (ulong i = 0; i < vtest.size(); i++)
  {
    ROSSI_TEST_BINARY_OP(i, *);
  }

}


// ------------------
void RossiBigInt::Test400_Operator_Division_Bigint()
{
ostringstream oss;
  oss << "RossiBigInt::Test400_Operator_Division_Bigint";

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  ROSSI_CREATE_EMPTY_VTEST;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0x10);
  ulong_nums.push_back (0x100);
  ulong_nums.push_back (0xFFFFFFFD);
  ulong_nums.push_back (0xFFFFFFFE);
  ulong_nums.push_back (0xFFFFFFFF);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }

  // --- hexstr_nums ---
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");


  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_STRING_HEX (hexstr_nums[i], hexstr_nums[k]);
    }
  }

  for (ulong i = 0; i < vtest.size(); i++)
  {
    ROSSI_TEST_BINARY_OP(i, /);
  }

}



// ------------------
void RossiBigInt::Test500_Operator_Reminder_Bigint()
{
ostringstream oss;
  oss << "RossiBigInt::Test500_Operator_Reminder_Bigint";

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  ROSSI_CREATE_EMPTY_VTEST;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0x10);
  ulong_nums.push_back (0x100);
  ulong_nums.push_back (0xFFFFFFFD);
  ulong_nums.push_back (0xFFFFFFFE);
  ulong_nums.push_back (0xFFFFFFFF);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }

  // --- hexstr_nums ---
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");


  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_STRING_HEX (hexstr_nums[i], hexstr_nums[k]);
    }
  }

  for (ulong i = 0; i < vtest.size(); i++)
  {
    ROSSI_TEST_BINARY_OP(i, %);
  }

}



// ------------------
void RossiBigInt::Test600_Operator_Less()
{
ostringstream oss;
  oss << "RossiBigInt::Test600_Operator_Less";

  cout << endl;
  cout << endl;
  cout << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << oss.str() << endl;
  cout << string (oss.str().size(), '-') << endl;
  cout << endl;


  ROSSI_CREATE_EMPTY_VTEST;

vector<ulong>  ulong_nums;
vector<string> hexstr_nums;

  // --- ulong_nums ---
  ulong_nums.push_back (0);
  ulong_nums.push_back (1);
  ulong_nums.push_back (2);
  ulong_nums.push_back (3);
  ulong_nums.push_back (9);
  ulong_nums.push_back (10);
  ulong_nums.push_back (11);
  ulong_nums.push_back (15);
  ulong_nums.push_back (16);
  ulong_nums.push_back (17);
  ulong_nums.push_back (0xFFFFFFFD);
  ulong_nums.push_back (0xFFFFFFFE);
  ulong_nums.push_back (0xFFFFFFFF);

  for (ulong i = 0; i < ulong_nums.size(); i++)
  {
    for (ulong k = 0; k < ulong_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_ULONG (ulong_nums[i], ulong_nums[k]);
    }
  }


  // --- hexstr_nums ---
  hexstr_nums.push_back ("0");
  hexstr_nums.push_back ("1");
  hexstr_nums.push_back ("2");
  hexstr_nums.push_back ("3");
  hexstr_nums.push_back ("100");
  hexstr_nums.push_back ("ABC");
  hexstr_nums.push_back ("F000000000000000");
  hexstr_nums.push_back ("FEDCBA9876543210");
  hexstr_nums.push_back ("123456789ABCDEF");
  hexstr_nums.push_back ("FFFFFFFFFFFFFFFFFFFFFFFF");
  hexstr_nums.push_back ("123456789ABCDEF123456789FFFFFFFFFFF");
  hexstr_nums.push_back ("111222333444555666777888999AAABBBCC");


  for (ulong i = 0; i < hexstr_nums.size(); i++)
  {
    for (ulong k = 0; k < hexstr_nums.size(); k++)
    {
      ROSSI_ADD_TEST_CASE_STRING_HEX (hexstr_nums[i], hexstr_nums[k]);
    }
  }


  for (ulong i = 0; i < vtest.size(); i++)
  {
    ROSSI_TEST_BOOLEAN_OP(i, <);
  }

}


// ------------------
void RossiBigInt::All_Tests()
{
  Test100_Operator_Add_Bigint();
  Test200_Operator_Subtraction_Bigint ();
  Test210_Operator_Subtraction_Bigint ();
  Test300_Operator_Multiplication_Bigint ();
  Test400_Operator_Division_Bigint ();
  Test500_Operator_Reminder_Bigint ();
  Test600_Operator_Less ();
}

// --------------------------
void RossiBigInt::assertCheck()
{
 	switch (sizeof (ulong))
  {
  	case 4:
  		assert (ULONG_MSB == 0x80000000);
  		break;
  		
  	case 8:
  		assert (ULONG_MSB == 0x8000000000000000LLU);
  		break;
  		
  	default:	
  		assert (0);
  		break;
  }
}  
	

