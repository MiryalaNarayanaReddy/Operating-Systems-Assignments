a.out:main.o stimer.o user.o person.o zone.o group.o goal.o 
	gcc main.o stimer.o user.o person.o zone.o group.o goal.o -o a.out -pthread

main.o: main.c
	gcc -c main.c

stimer.o: stimer.c
	gcc -c stimer.c

user.o: user.c
	gcc -c user.c

person.o: person.c
	gcc -c person.c

zone.o: zone.c 
	gcc -c zone.c

group.o: group.c 
	gcc -c group.c

goal.o : goal.c
	gcc -c goal.c 

clean:
	rm *.o
