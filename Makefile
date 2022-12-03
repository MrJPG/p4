all: p4

monticulo.o: monticulo.c monticulo.h
	gcc -c -Wall monticulo.c

p4.o: p4.c monticulo.h
	gcc -c -Wall p4.c

p4: p4.o monticulo.o
	gcc -Wall p4.o monticulo.o -o p4 -lm

clean:
	rm -f p4.o monticulo.o  p4

