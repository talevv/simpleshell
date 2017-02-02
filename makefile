nekoshell: main.o nekoshell.o
	gcc main.o nekoshell.o -o nekoshell

main.o: main.c
	gcc -c main.c

nekoshell.o: nekoshell.c nekoshell.h
	gcc -c nekoshell.c

clean:
	rm *.out