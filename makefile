sources = ./lib/sources
headers = ./lib/headers

nekoshell: main.o nekoshell.o
	gcc main.o nekoshell.o -o nekoshell

main.o: main.c
	gcc -c main.c

nekoshell.o: $(sources)/nekoshell.c $(headers)/nekoshell.h
	gcc -c $(sources)/nekoshell.c
