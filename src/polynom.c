#include "polynom.h"
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

polynom makePolynom(num a[], int deg) {
	polynom f;
	f.deg = deg;
	for (; deg > 0; deg--) {
		f.p[deg] = a[deg];
	}
	return f;
}


num calcPolynom(polynom f, num x) {
	num value = makeNum(0,1);
	for (int i = 0; i <= f.deg; i++) {
		value = optimiseNum(addNum(value, mplNum(f.p[i], powerNumInt(x,i))));
	}
	return value;
}

polynom addPolynom(polynom f, polynom g) {
	polynom h;
	h.deg = MAX(f.deg,g.deg);
	int i = 0;
	for (;  i < MIN(f.deg,g.deg);i++) {
		h.p[i] = optimiseNum(addNum(f.p[i], g.p[i]));
	}
	for (; i <= h.deg; i++ ) {
		if (f.deg == h.deg)
			h.p[i] = f.p[i];
		else
			h.p[i] = g.p[i];
	}
	num j = h.p[h.deg];
	while (optimiseNum(j).numerator == 0) {
		h.deg--;
		j = h.p[h.deg];
	}
	return h;
}

polynom mplPolynom(polynom f, polynom g) {
	polynom h;
	h.deg = f.deg + g.deg;
	for (int i = 0; i <= h.deg; i++) {
		num value;
		for (int j = 0; j <= f.deg; j++) {
			for (int k = 0; k <= g.deg; k++) {
				if (j + k == i)
					value = optimiseNum(addNum(value, mplNum(optimiseNum(f.p[j]), optimiseNum(g.p[k]))));
			}
		}
		h.p[i] = value;
	}
	num i = h.p[h.deg];
	while (optimiseNum(i).numerator == 0) {
		h.deg--;
		i = h.p[h.deg];
	}
	return h;
}

polynom derivePolynom(polynom f) {
	polynom h;
	h.deg = f.deg - 1;
	for (int i = f.deg; i > 0; i--) {
		h.p[i - 1] = optimiseNum(mplNum(f.p[i] , makeNum(i, 1)));
	}
	return h;

}

polynom intergrate(polynom f) {
	polynom F;
	F.deg = f.deg + 1;
	for (int i = F.deg; i > 0; i--) {
		F.p[i] = optimiseNum(mplNum(f.p[i-1], makeNum(1, i)));
	}
	F.p[0] = makeNum(0,1);
	return F;
}

divisoremainder divPolynom(polynom f, polynom g) {
	divisoremainder ret;
	polynom res;
	res.deg = f.deg - g.deg;
	num negNumAr[] = {makeNum(-1,1)};
	polynom neg = makePolynom(negNumAr, 0);
	while (f.deg >= g.deg) {
		res.p[g.deg-f.deg] = optimiseNum(divfullNum( f.p[f.deg] , g.p[g.deg]));
		f = addPolynom(mplPolynom(neg,f), g);
	}
	ret.f = res;
	ret.remainder = f;
	num i = f.p[f.deg];
	while (optimiseNum(i).numerator == 0) {
		f.deg--;
		i = f.p[f.deg];
	}

	return ret;

}
