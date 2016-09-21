/* This assignment originated at UC Riverside.*/
 
#include <string>
#include "hash.h"
#include <math.h>

using std::string;

// The Hash function I copied is the Bernstein hash. I tried to 
//make my own by bit shifts bitwise functions among random/constant
//multipliers I made no modifications to it, I will say where I got it from
// www.eternallyconfuzzled.com

//the Bernstein hash utilizes a constant multiplier of 33 it is not really
//known why the number works so well because it is not a prime number
//but for the length of the array you will times a value by 33 + the asci of 
//the current char's ascii value

//int Hash::hf ( string ins ) {
  //int h=0;
//  int i=0;
  //for(i=0;i<((int)ins.length());i++) {
 // h=33*h+ins[i];
  //}
 // return ( h % HASH_TABLE_SIZE);
//}

int Hash::hf (string ins) {
return ((int)ins[0]) % HASH_TABLE_SIZE;
}
