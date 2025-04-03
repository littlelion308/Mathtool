#include "genericVar.h"
#include <stdlib.h>

void *varCopy(void *vtC) {
	ringVar *tC = (ringVar *)vtC;
	ringVar *cped = malloc(sizeof(ringVar));
	cped->val = tC->ring->gen.copy(tC->val);
	cped->ring = tC->ring;
	return cped;
}

void varFree(void *vtF) {
	ringVar *tF = (ringVar *)vtF;
	tF->ring->gen.mFree(tF->val);
	free(tF);
}
