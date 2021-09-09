# linking
Narshell: main.o user.o cd.o
	gcc main.o user.o cd.o -o Narshell

###  object files

## shell

main.o: Shell/main.c
	gcc -c Shell/main.c

user.o: Shell/user.c
	gcc -c Shell/user.c

## cd
cd.o: cd/cd.c
	gcc -c cd/cd.c

## ls


# clean all object files
clean:
	rm *.o
