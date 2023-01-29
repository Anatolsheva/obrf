
all: pobr.o oplik.o strukobr.o
	gcc -o obrazy2 pobr.o oplik.o strukobr.o odczyt.c -lm

pobr.o: pobr.c pobr.h strukobr.o
	gcc -c pobr.h strukobr.o pobr.c

oplik.o: oplik.c oplik.h strukobr.o
	gcc -c oplik.h strukobr.o oplik.c

strukobr.o: strukobr.c strukobr.h
	gcc -c strukobr.h strukobr.c
	
clean:
	rm -f *.o obrazy2
