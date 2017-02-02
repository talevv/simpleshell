nekoshell: main.o nekoshell.o
	gcc main.o nekoshell.o -o nekoshell

main.o: main.c
	gcc -c main.c

nekoshell.o: ./lib/sources/nekoshell.c ./lib/headers/nekoshell.h
	gcc -c ./lib/sources/nekoshell.c

clean:
	rm *.out