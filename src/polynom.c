#include "polynom.h"
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

const ring getPolynomRing(field *f) {
	polynom addneutural = makePolynom(f->add.neutral,0);
	group fracAdd = {&addPolynom, &addneutural, &addInvertPolynom, &subPolynom};
	polynom mplneutural = makePolynom(f->mpl.neutral,1);
	monoid fracMpl = {&mplPolynom, &mplneutural};
	const genops gOps = {&optimisePolynom, &copyPolynom, &freePolynom};
	ring fracField = {fracAdd, fracMpl, gOps, "Polynom R"};
	return fracField;
}

void *copyPolynom(void *vf){
	polynom *f = (polynom *)vf;
	field bf = *(f->p[0].field);
	f = (polynom *)optimisePolynom(f);
	polynom *g = malloc(sizeof(unsigned int) + sizeof(fieldVar) * (f->deg + 1));
	g->deg = f->deg;
	for (int i = 0; i < f->deg; i++)
		g->p[i] = *(fieldVar *)bf.gen.copy(&f->p[i]);
	return g;
}

void freePolynom(void *vf) {
	polynom *f = (polynom *)vf;
	for (int i = 0; i <= f->deg; i++)
		varFree(&(f->p[i]));
	free(f);
}

void *optimisePolynom(void *vf) {
	polynom *f = (polynom *)((ringVar *)vf)->val;
	// optimize The Numbers
	for (int i = 0; i <= f->deg; i++)
		f->p[0].field->gen.optimise(&f->p[i]);
	// optimize the size
	int i = f->deg;
	while (i > 0 && f->p[i].val == f->p[0].field->add.neutral)
		i--;
	polynom *g = malloc(sizeof(unsigned int) + sizeof(fieldVar) * (i + 1));
	g->deg = i;
	memcpy(g->p, f->p, sizeof(fieldVar) * (i +1));
	freePolynom(f);
	fieldVar *rf = (fieldVar *)vf;
	rf->val = g;
	return rf;
}


polynom makePolynom(fieldVar a[], int deg) {
	polynom f;
	f.deg = deg;
	for (; deg > 0; deg--) {
		f.p[deg] = a[deg];
	}
	f = *(polynom *)optimisePolynom(&f);
	return f;
}


fieldVar *calcPolynom(ringVar *vf, void *vx) {
	polynom *f = vf->val;
	fieldVar *x = (fieldVar *)vx;
	fieldVar neut = {x->field->add.neutral, x->field};
	fieldVar *value = &neut;
	for (int i = 0; i <= f->deg; i++) {
		fieldVar *toadd = x->field->mpl.neutral;
		for (int j = 1; j <= i; j++) {
			fieldVar *b = x->field->mpl.op(x, toadd);
			free (toadd);
			toadd = b;
		}
		fieldVar *b = x->field->add.op(value, x->field->mpl.op(&(f->p[i]), toadd));
		free(value);
		value = b;
	}
	x->field->gen.optimise(&value);
	return value;
}

void *addPolynom(void *vf, void *vg) {
	polynom *f = (polynom *)((ringVar *)vf)->val;
	polynom *g = (polynom *)((ringVar *)vg)->val;
	field bf = *(f->p[0].field);
	polynom h;
	h.deg = MAX(f->deg,g->deg);
	int i = 0;
	for (;  i < MIN(f->deg,g->deg);i++) {

		h.p[i].val = ((bf.add.op((f->p[i].val), (g->p[i]).val)));
		bf.gen.optimise(&h.p[i]);
		h.p[i].field = (f->p[0].field);
	}
	for (; i <= h.deg; i++ ) {
		if (f->deg == h.deg)
			h.p[i] = f->p[i];
		else
			h.p[i] = g->p[i];
	}
	void *j = copyPolynom(&h);
	j = (polynom *)optimisePolynom(j);
	ringVar *rj;
	rj->val = j;
	rj->ring = ((ringVar *)vf)->ring;
	return rj;
}


void *addInvertPolynom(void *f) {
	ringVar *rg = (ringVar *)varCopy(f);
	polynom *g = rg->val;
	field bf = *(g)->p[0].field;
	for (int i = 0; i <= g->deg; i++) {
		fieldVar *a = bf.add.invert( &(g->p[i]));
		varFree(&(g->p[i]));
		g->p[i] = *a;
		varFree(a);
	}

	return g;
}


void *subPolynom(void *f, void *g) {
	ringVar *h = addInvertPolynom(g);
	ringVar *i = addPolynom(f,h);
	varFree(h);
	return i;
}

void *mplPolynom(void *vf, void *vg) {
	polynom *f = (polynom *)((ringVar *)vf)->val;
	polynom *g = (polynom *)((ringVar *)vg)->val;
	field bf = *(f->p[0].field);
	polynom h;
	h.deg = f->deg + g->deg;
	for (int i = 0; i <= h.deg; i++) {
		fieldVar value;
		for (int j = 0; j <= f->deg; j++) {
			for (int k = 0; k <= g->deg; k++) {
				if (j + k == i) {
					fieldVar *c = bf.mpl.op(&f->p[i], &g->p[i]);
					fieldVar *b = bf.add.op(&value, &c);
					value = *b;
					free(b);
					free(c);
				}
			}
		}
		h.p[i] = value;
	}
	void *j = copyPolynom(&h);
	ringVar *rj;
	rj->val = j;
	rj->ring = ((ringVar *)vf)->ring;
	return rj;
}

ringVar *derivePolynom(ringVar *rf) {
	polynom *f = rf->val;
	if (strcmp(f->p[0].field->name, "Rational F") != 0 || strcmp(f->p[0].field->name, "Real F") != 0 )
		return NULL;
	polynom h;
	h.deg = f->deg - 1;
	for (int i = f->deg; i > 0; i--) {
		fieldVar *inta;
		if (strcmp(f->p[0].field->name, "Rational F") == 0)
			inta = makeFracFromInts(i, 1);
		h.p[i - 1] = *(fieldVar *)inta->field->mpl.op(inta, &f->p[i]);
		varFree(inta);
	}
	void *j = copyPolynom(&h);
	ringVar *rj;
	rj->val = j;
	rj->ring = rf->ring;
	return rj;

}

ringVar *intergrate(ringVar *rf) {
	polynom *f = rf->val;
	if (strcmp(f->p[0].field->name, "Rational F") != 0 || strcmp(f->p[0].field->name, "Real F") != 0 )
		return NULL;
	polynom F;
	F.deg = f->deg + 1;
	for (int i = F.deg - 1; i >= 0; i--) {
		fieldVar *inta;
		if (strcmp(f->p[0].field->name, "Rational F") == 0)
			inta = makeFracFromInts(1, i);
		F.p[i + 1] = *(fieldVar *)inta->field->mpl.op(inta, &f->p[i]);
		varFree(inta);
	}
	if (strcmp(f->p[0].field->name, "Rational F") == 0)
		F.p[0] = *makeFracFromInts(0,1);
	void *j = copyPolynom(&F);
	ringVar *rj;
	rj->val = j;
	rj->ring = rf->ring;
	return rj;
}

divisorremainder divPolynom(ringVar *rf, ringVar *rg) {
	polynom *f = rf->val;
	polynom *g = rg->val;
	field bf = *(f->p[0].field);
	divisorremainder ret;
	polynom res;
	res.deg = f->deg - g->deg;
	polynom *h = copyPolynom(f);
	while (h->deg >= g->deg) {
		res.p[g->deg - h->deg] = *(fieldVar *)bf.mpl.invOp( &h->p[h->deg] , &g->p[g->deg]);
		polynom *i = subPolynom(h, g);
		freePolynom(h);
		h = i;
	}
	void *j = copyPolynom(&res);
	ringVar rres;
	rres.val = j;
	rres.ring = rf->ring;
	ret.divisor = rres;

	void *k = copyPolynom(&h);
	ringVar rrem;
	rrem.val = j;
	rrem.ring = rf->ring;
	ret.remainder = rrem;

	optimisePolynom(ret.remainder.val);
	optimisePolynom(ret.divisor.val);

	return ret;

}
