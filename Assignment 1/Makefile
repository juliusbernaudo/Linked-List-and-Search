dict: dict.o list.o
	gcc -o dict dict.o list.o

list.o: list.c list.h
	gcc -c -Wall list.c

dict.o: dict.c list.h
	gcc -c -Wall dict.c