DEFFAGS = -Wall
FINFAGS = -O3
OBJS = out/frac.o out/matrix.o

exec: $(OBJS) outdir
	gcc $(DEFFAGS) -o main src/exec.c $(OBJS)
	chmod +x main

out/matrix.o: src/matrix.c src/matrix.h
	mkdir -p out
	gcc $(DEFFAGS) -c src/matrix.c -o out/matrix.o

out/frac.o: src/frac.c src/frac.h
	mkdir -p out
	gcc $(FINFAGS) -c src/frac.c -o out/frac.o

outdir:
	mkdir -p out

run: exec
	./main

clean:
	rm -rf ./out
	rm  -f ./main
