all: klgout clean
klgout: klg.o
	gcc -o klg klg.o
klg.o: klg.c
	gcc -Wall -g -c klg.c
clean:
	rm -f klg.o
