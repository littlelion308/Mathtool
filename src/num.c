#include "num.h"
#include <limits.h>
#include <stdio.h>

num optimiseNum(num a) {
	return optimiseRealnum(a);
}


num addNum(num a, num b) {
	return addRealnum(a, b);
}

num subNum(num a, num b) {
	return subRealnum(a, b);
}

num mplNum(num a, num b) {
	return mplRealnum(a, b);
}

num divfullNum(num a, num b) {
	return divRealnum(a ,b);

}
/* num power(num a, num b) {} */

num powerNumInt(num base, int exponent) {
	return powerRealnumInt(base, exponent);
}

num makeNum(int numerator, int denominator) {
	return makerealnum(numerator, denominator);
}
double convertNumToDouble(num a) {
	return realnumToDouble(a);
}
float convertNumToFloat(num a) {
	return convertNumToFloat(a);
}

void printNum(num a) {
	printRealnum(a);
}
