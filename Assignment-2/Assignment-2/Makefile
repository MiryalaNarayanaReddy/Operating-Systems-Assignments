# linking
a.out: main.o user.o utils.o cd.o echo.o
	gcc main.o user.o utils.o cd.o echo.o -o a.out

###  object files

## shell

main.o: Shell/main.c
	gcc -c Shell/main.c

user.o: Shell/user.c
	gcc -c Shell/user.c

utils.o: Shell/utils.c
	gcc -c Shell/utils.c

## builtin_commands
cd.o: builtin_commands/cd.c
	gcc -c builtin_commands/cd.c

echo.o: builtin_commands/echo.c
	gcc -c builtin_commands/echo.c

## ls


# clean all object files
clean:
	rm *.o
