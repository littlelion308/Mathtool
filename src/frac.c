#include "frac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


field getFracField() {
	const frac addneutural = makeFrac(0,1);
	const group fracAdd = {&addFrac, &addneutural, &subFromZeroFrac, &subFrac};
	const frac mplneutural = makeFrac(1,1);
	const group fracMpl = {&mplFrac, &mplneutural, &mplMOneFrac, &divideFrac};
	const genops gOps = {&optimiseFrac, &copyFrac, &freeFrac};
	const field fracField = {fracAdd, fracMpl, gOps, "Rational F"};
	return fracField;
}

ring getFracRing() {
	const frac addneutural = makeFrac(0,1);
	const group fracAdd = {&addFrac, &addneutural, &subFromZeroFrac, &subFrac};
	const frac mplneutural = makeFrac(1,1);
	const monoid fracMpl = {&mplFrac, &mplneutural};
	const genops gOps = {&optimiseFrac, &copyFrac, &freeFrac};
	const ring fracField = {fracAdd, fracMpl,gOps, "Rational R"};
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

void freeFrac(void *a) {
	free(a);
}


void *optimiseFrac(void *input) {
	ringVar *ringVara = (ringVar *)input;
	frac *a = (frac *)ringVara->val;
	int num = a->numerator;
	int den = a->denominator;
	if (num == 0) {
		a->numerator = 0;
		a->denominator = 1;
		return input;
	}
	if (den < 0) {
		a->numerator *= -1;
		a->denominator *= -1;
	}
	if (den == 0) {
		a->numerator = num > 0 ? INT_MAX : INT_MIN;
		a->denominator = 0;
		return input;
	}
	int div = gcd(num, den);
	a->numerator = num/div;
	a->denominator = den/div;
	return input;
}

// writtern in case it ever gets needed
/* frac static extend(frac a, int b) { */
/* 	return  makeFrac(a.numerator * b, a.denominator * b); */
/* } */


void *copyFrac(void *a) {
	void *b = malloc(sizeof(frac));
	memcpy(b, a, sizeof(frac));
	return b;
}

void *addFrac(void *va, void *vb) {
	ringVar *ra = (ringVar *)va;
	ringVar *rb = (ringVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->denominator) + (b->numerator * a->denominator), a->denominator * b->denominator);
	c = *(frac *)optimiseFrac((void *)&c);
	ringVar *rc;
	rc->val = copyFrac(&c);
	rc->ring = ra->ring;
	return varCopy(rc);
}

void *subFromZeroFrac(void *a) {
	ringVar neuturalRing = {getFracRing().add.neutral, ((ringVar *)a)->ring};
	return subFrac(&neuturalRing, a);
}

void *subFrac(void *va, void *vb) {
	ringVar *ra = (ringVar *)va;
	ringVar *rb = (ringVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->denominator) - (b->numerator * a->denominator), a->denominator * b->denominator);
	c = *(frac *)optimiseFrac((void *)&c);
	ringVar *rc;
	rc->val = copyFrac(&c);
	rc->ring = ra->ring;
	return varCopy(rc);
}


void *mplFrac(void *va, void *vb) {
	ringVar *ra = (ringVar *)va;
	ringVar *rb = (ringVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->numerator), a->denominator * b->denominator);
	c = *(frac *)optimiseFrac((void *)&c);
	ringVar *rc;
	rc->val = copyFrac(&c);
	rc->ring = ra->ring;
	return varCopy(rc);
}

void *mplMOneFrac(void *a) {
	ringVar neuturalRing = {getFracRing().mpl.neutral, ((ringVar *)a)->ring};
	return divideFrac(&neuturalRing, a);
}

void *divideFrac(void *va, void *vb) {
	fieldVar *ra = (fieldVar *)va;
	fieldVar *rb = (fieldVar *)vb;
	frac *a = (frac *)ra;
	frac *b = (frac *)rb;
	frac c = makeFrac((a->numerator * b->denominator), a->denominator * b->numerator);
	c = *(frac *)optimiseFrac((void *)&c);
	fieldVar *rc;
	rc->val = copyFrac(&c);
	rc->field = ra->field;
	return varCopy(rc);
}
/* frac power(frac a, frac b) {} */

frac power(frac base, int exponent) {
	frac ret = base;
	if (exponent == 0) return makeFrac(1,1);
	if (exponent > 1)
		for (; exponent > 1; exponent--)
			ret = *(frac *)mplFrac(&ret, &base);
	else if (exponent < 0)
		for (; exponent < 1; exponent++)
			ret = *(frac *)divideFrac(&ret, &base);
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

fieldVar *makeFracFromInts(int a, unsigned int b){
	fieldVar *ret = malloc(sizeof(ringVar));
	field fielda = getFracField();
	ret->field = &fielda;
	frac inta = makeFrac(a, b);
	ret->val = &inta;

	return ret;
}
