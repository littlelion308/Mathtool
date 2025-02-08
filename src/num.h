// decided the algorithmes should also work in other real Numbers
// thogh this schould start later
#include "realNum.h"

#ifndef NUM
#define NUM
// This is the string of the type of num
#define NUM_TYPE realnum
#define NUM_METHODE Realnum
typedef NUM_TYPE num;
#endif

num optimiseNum(num a);
num makeNum(int numerator, int denominator);
double convertNumToDouble(num a);
float convertNumToFloat(num a);
void printNum(num a);
num addNum(num a, num b);
num subNum(num a, num b);
num mplNum(num a, num b);
num divfullNum(num a, num b);
num powerNumInt(num base, int exponent);
