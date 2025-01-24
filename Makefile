DEFFAGS = -Wall
FINFAGS = -O3
OBJS = out/frac.o out/polynom.o out/num.o

exec: $(OBJS) outdir
	gcc $(DEFFAGS) -o main src/exec.c $(OBJS)
	chmod +x main

out/matrix.o: src/matrix.c src/matrix.h out/frac.o
	mkdir -p out
	gcc $(DEFFAGS) -c src/matrix.c -o out/matrix.o

out/frac.o: src/frac.c src/frac.h
	mkdir -p out
	gcc $(FINFAGS) -c src/frac.c -o out/frac.o

out/num.o: out/frac.o src/num.c src/num.h
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
