// ==============================================================
//
//  Copyright (C) 2004-2009  Alex Vinokur.
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
//  FILE     : main.cpp
//
//  DESCRIPTION :
//          Nain program
//
// ##############################################################


// ===============
#include "bigint.h"
// ===============

// -------------------
static void show_help (int argc, char** argv)
{
  cerr << endl;
  cerr << "USAGE: " << argv[0] << endl;
  cerr << "     : " << argv[0] << " first-arg binary-operation second-arg" << endl;
  cerr << endl;
}


static map<string, string> allowed_operations;
// -------------------
static bool check (int argc, char** argv)
{
  ::ShowVersion();

  if (allowed_operations.empty())
  {
    allowed_operations["+"] = "Addition";
    allowed_operations["-"] = "Subtraction";
    allowed_operations["x"] = "Multiplication";
    allowed_operations["/"] = "Division";
    allowed_operations["%"] = "Reminder";
  }

  // TO BE UPGRADED
  switch (argc)
  {
    case 1:
      show_help (argc, argv);
      return true;
      break;  // unused

    case 4:
      if (!allowed_operations.count (argv[2]))
      {
        cerr << "Illegal operation in argv[2] : " << argv[2] << endl;
        cerr << "Allowed operations are as follows: ";
        for (map<string, string>::const_iterator pos_iter = allowed_operations.begin();  
             pos_iter != allowed_operations.end(); 
             pos_iter++
             )
        {
          cerr << pos_iter->first << " ";  
        }
        cerr << endl;
        cerr << endl;
        return false;
      }
      return true;
      break; 
    
    default:
      show_help (argc, argv);
      return false;
      break;  // unused
  }
  
  assert (0);
  return false;
}

// -------------------
static void run_rossi (int argc, char** argv)
{
  assert (!allowed_operations.empty());

const string str1 (argv[1]);
const string str2 (argv[3]);

RossiBigInt arg1 (str1, DEC_DIGIT);
string op (argv[2]);
RossiBigInt arg2 (str2, DEC_DIGIT);

RossiBigInt res;

  assert (allowed_operations.count(op));

  if (op == "+") res = arg1 + arg2;
  if (op == "-") res = arg1 - arg2;
  if (op == "x") res = arg1 * arg2;
  if (op == "/") res = arg1 / arg2;
  if (op == "%") res = arg1 % arg2;

  cout << arg1 << " " << op << " " << arg2 << " = " << res << endl;
}


// ===================
//int main (int argc, char** argv)
//{
//	RossiBigInt::assertCheck();
//	
//  if (!check (argc, argv)) return 1;
//
//  if (argc == 1)
//  {
//    VinBigInt::All_Tests();
//    RossiBigInt::All_Tests();
//    show_help (argc, argv);
//    return 0;
//  }
//  assert (argc == 4);
//
//  run_rossi (argc, argv);
//
//  
//  return 0;
//
//}


