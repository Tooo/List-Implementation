all: test.c list.c list.h
	gcc -o test -Wall test.c list.c

clean:
	rm test