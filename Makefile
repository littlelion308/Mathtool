CFAGS = -Wall
FINFAGS = -O3
OBJS = frac.o

exec: out/$(OBJS) outdir
	gcc $(CFAGS) -o main src/exec.c out/$(OBJS)
	chmod +x main


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
