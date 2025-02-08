DEFFAGS = -Wall
FINFAGS = -O3
OBJS = out/polynom.o out/num.o

NUM_FILE = out/realnum.o
NUMBERS = out/frac.o out/realnum.o

exec: $(OBJS) outdir
	gcc $(DEFFAGS) -o main src/exec.c $(OBJS) $(NUMBERS)
	chmod +x main

out/matrix.o: src/matrix.c src/matrix.h out/frac.o
	mkdir -p out
	gcc $(DEFFAGS) -c src/matrix.c -o out/matrix.o

out/frac.o: src/frac.c src/frac.h
	mkdir -p out
	gcc $(FINFAGS) -c src/frac.c -o out/frac.o

out/realnum.o: src/realnum.c src/realnum.h
	mkdir -p out
	gcc $(FINFAGS) -c src/realNum.c -o out/realNum.o


out/num.o: src/num.c src/num.h $(NUM_FILE)
	mkdir -p out
	gcc $(FINFAGS) -c src/num.c -o out/num.o

out/polynom.o: src/polynom.c src/polynom.h out/frac.o
	mkdir -p out
	gcc $(DEFFAGS) -c src/polynom.c -o out/polynom.o

outdir:
	mkdir -p out

run: exec
	./main

clean:
	rm -rf ./out
	rm  -f ./main
