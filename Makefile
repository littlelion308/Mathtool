DEFFAGS = -Wall
FINFAGS = -O3
OBJS = frac.o matrix.o

exec: out/$(OBJS) outdir
	gcc $(DEFFAGS) -o main src/exec.c out/$(OBJS)
	chmod +x main

out/matrix.o: src/matrix.c src/matrix.h
	makedir -p out
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
