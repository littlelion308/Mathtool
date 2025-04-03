#include "frac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


field getFracField() {
	const frac addneutural = makeFrac(0,1);
	const group fracAdd = {&add, &addneutural, &subFromZero, &sub, &copy};
	const frac mplneutural = makeFrac(1,1);
	const group fracMpl = {&mpl, &mplneutural, &mplMOne, &divide, &copy};
	const field fracField = {fracAdd, fracMpl, &optimise};
	return fracField;
}

ring getFracRing() {
	const frac addneutural = makeFrac(0,1);
	const group fracAdd = {&add, &addneutural, &subFromZero, &sub, &copy};
	const frac mplneutural = makeFrac(1,1);
	const monoid fracMpl = {&mpl, &mplneutural, &copy};
	const ring fracField = {fracAdd, fracMpl, &optimise};
	return fracField;
}

int gcd(int a, int b) {
	if (a < 0) a = (-a);
	if (b < 0) b = (-b);
	if (a == b) return a;
	if (a < b) {
		int get = a;
		a = b;
		b = get;
	}
//      a > b
	int rem = a % b;
	if (rem == 0) return b;
	return gcd(b, rem);


}

void optimise(void *input) {
	ringVar *ringVara = (ringVar *)input;
	frac *a = (frac *)ringVara->val;
	int num = a->numerator;
	int den = a->denominator;
	if (num == 0) {
		a->numerator = 0;
		a->denominator = 1;
		return;
	}
	if (den < 0) {
		a->numerator *= -1;
		a->denominator *= -1;
	}
	if (den == 0) {
		a->numerator = num > 0 ? INT_MAX : INT_MIN;
		a->denominator = 0;
		return;
	}
	int div = gcd(num, den);
	a->numerator = num/div;
	a->denominator = den/div;
}

// writtern in case it ever gets needed
/* frac static extend(frac a, int b) { */
/* 	return  makeFrac(a.numerator * b, a.denominator * b); */
/* } */


void *copy(void *a) {
	void *b = malloc(sizeof(frac));
	memcpy(b, a, sizeof(frac));
	return b;
}

void *add(void *va, void *vb) {
	ringVar *ra = (ringVar *)va;
	ringVar *rb = (ringVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->denominator) + (b->numerator * a->denominator), a->denominator * b->denominator);
	optimise((void *)&c);
	ringVar *rc;
	rc->val = copy(&c);
	rc->ring = ra->ring;
	return copy(&rc);
}

void *subFromZero(void *a) {
	ringVar neuturalRing = {getFracRing().add.neutral, ((ringVar *)a)->ring};
	return sub(&neuturalRing, a);
}

void *sub(void *va, void *vb) {
	ringVar *ra = (ringVar *)va;
	ringVar *rb = (ringVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->denominator) - (b->numerator * a->denominator), a->denominator * b->denominator);
	optimise((void *)&c);
	ringVar *rc;
	rc->val = copy(&c);
	rc->ring = ra->ring;
	return copy(&rc);
}


void *mpl(void *va, void *vb) {
	ringVar *ra = (ringVar *)va;
	ringVar *rb = (ringVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->numerator), a->denominator * b->denominator);
	optimise((void *)&c);
	ringVar *rc;
	rc->val = copy(&c);
	rc->ring = ra->ring;
	return copy(&rc);
}

void *mplMOne(void *a) {
	ringVar neuturalRing = {getFracRing().mpl.neutral, ((ringVar *)a)->ring};
	return divide(&neuturalRing, a);
}

void *divide(void *va, void *vb) {
	fieldVar *ra = (fieldVar *)va;
	fieldVar *rb = (fieldVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->denominator), a->denominator * b->numerator);
	optimise((void *)&c);
	fieldVar *rc;
	rc->val = copy(&c);
	rc->field = ra->field;
	return copy(&rc);
}
/* frac power(frac a, frac b) {} */

frac power(frac base, int exponent) {
	frac ret = base;
	if (exponent == 0) return makeFrac(1,1);
	if (exponent > 1)
		for (; exponent > 1; exponent--)
			ret = *(frac *)mpl(&ret, &base);
	else if (exponent < 0)
		for (; exponent < 1; exponent++)
			ret = *(frac *)divide(&ret, &base);
	return ret;
}

frac makeFrac(int numerator, int denominator) {
	frac ret;
	ret.denominator = denominator;
	ret.numerator   = numerator;
	return ret;
}
double toDouble(frac a) {
	return a.numerator/a.denominator;
}
float toFloat(frac a) {
	return a.numerator/a.denominator;
}

void printFrac(frac a) {
	printf("%d/%d\n", a.numerator, a. denominator);
}
