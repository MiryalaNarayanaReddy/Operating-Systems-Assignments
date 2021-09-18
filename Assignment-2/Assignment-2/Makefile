# linking
a.out: main.o user.o utils.o cd.o echo.o pwd.o ls.o process.o pinfo.o signal_handler.o init.o repeat.o
	gcc main.o user.o utils.o cd.o echo.o pwd.o ls.o process.o pinfo.o signal_handler.o init.o repeat.o -o a.out

###  object files

## shell

main.o: Shell/main.c
	gcc -c Shell/main.c

user.o: Shell/user.c
	gcc -c Shell/user.c

utils.o: Shell/utils.c
	gcc -c Shell/utils.c

signal_handler.o: Shell/signal_handler.c
	gcc -c Shell/signal_handler.c

init.o:Shell/init.c
	gcc -c Shell/init.c

## builtin_commands

cd.o: builtin_commands/cd.c
	gcc -c builtin_commands/cd.c

echo.o: builtin_commands/echo.c
	gcc -c builtin_commands/echo.c

pwd.o: builtin_commands/pwd.c
	gcc -c builtin_commands/pwd.c

## ls

ls.o: ls/ls.c
	gcc -c ls/ls.c

## system_commands

process.o: system_commands/process.c
	gcc -c system_commands/process.c

pinfo.o: system_commands/pinfo.c
	gcc -c system_commands/pinfo.c

repeat.o: system_commands/repeat.c
	gcc -c system_commands/repeat.c

# clean all object files
clean:
	rm *.o
