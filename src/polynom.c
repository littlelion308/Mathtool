#include "polynom.h"
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

polynom makePolynom(realnum a[], int deg) {
	polynom f;
	f.deg = deg;
	for (; deg > 0; deg--) {
		f.p[deg] = a[deg];
	}
	return f;
}


realnum calcPolynom(polynom f, realnum x) {
	realnum value = makerealnum(0,1);
	for (int i = 0; i <= f.deg; i++) {
		value = optimiseRealnum(addRealnum(value, mplRealnum(f.p[i], powerRealnum(x,i))));
	}
	return value;
}

polynom addPolynom(polynom f, polynom g) {
	polynom h;
	h.deg = MAX(f.deg,g.deg);
	int i = 0;
	for (;  i < MIN(f.deg,g.deg);i++) {
		h.p[i] = optimiseRealnum(addRealnum(f.p[i], g.p[i]));
	}
	for (; i <= h.deg; i++ ) {
		if (f.deg == h.deg)
			h.p[i] = f.p[i];
		else
			h.p[i] = g.p[i];
	}
	realnum j = h.p[h.deg];
	while (optimiseRealnum(j).numerator == 0) {
		h.deg--;
		j = h.p[h.deg];
	}
	return h;
}

polynom mplPolynom(polynom f, polynom g) {
	polynom h;
	h.deg = f.deg + g.deg;
	for (int i = 0; i <= h.deg; i++) {
		realnum value;
		for (int j = 0; j <= f.deg; j++) {
			for (int k = 0; k <= g.deg; k++) {
				if (j + k == i)
					value = optimiseRealnum(addRealnum(value, mplRealnum(optimiseRealnum(f.p[j]), optimiseRealnum(g.p[k]))));
			}
		}
		h.p[i] = value;
	}
	realnum i = h.p[h.deg];
	while (optimiseRealnum(i).numerator == 0) {
		h.deg--;
		i = h.p[h.deg];
	}
	return h;
}

polynom derivePolynom(polynom f) {
	polynom h;
	h.deg = f.deg - 1;
	for (int i = f.deg; i > 0; i--) {
		h.p[i - 1] = optimiseRealnum(mplRealnum(f.p[i] , makerealnum(i, 1)));
	}
	return h;

}

polynom intergrate(polynom f) {
	polynom F;
	F.deg = f.deg + 1;
	for (int i = F.deg; i > 0; i--) {
		F.p[i] = optimiseRealnum(mplRealnum(f.p[i-1], makerealnum(1, i)));
	}
	F.p[0] = makerealnum(0,1);
	return F;
}

divisoremainder divPolynom(polynom f, polynom g) {
	divisoremainder ret;
	polynom res;
	res.deg = f.deg - g.deg;
	realnum negNumAr[] = {makerealnum(-1,1)};
	polynom neg = makePolynom(negNumAr, 0);
	while (f.deg >= g.deg) {
		res.p[g.deg-f.deg] = optimiseRealnum(divRealnum( f.p[f.deg] , g.p[g.deg]));
		f = addPolynom(mplPolynom(neg,f), g);
	}
	ret.f = res;
	ret.remainder = f;
	realnum i = f.p[f.deg];
	while (optimiseRealnum(i).numerator == 0) {
		f.deg--;
		i = f.p[f.deg];
	}

	return ret;

}
