# linking
a.out: main.o user.o utils.o cd.o
	gcc main.o user.o utils.o cd.o -o a.out

###  object files

## shell

main.o: Shell/main.c
	gcc -c Shell/main.c

user.o: Shell/user.c
	gcc -c Shell/user.c

utils.o: Shell/utils.c
	gcc -c Shell/utils.c

## cd
cd.o: cd/cd.c
	gcc -c cd/cd.c

## ls


# clean all object files
clean:
	rm *.o
