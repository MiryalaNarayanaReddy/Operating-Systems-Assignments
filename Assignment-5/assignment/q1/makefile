a.out:main.o course.o student.o lab.o user.o stimer.o
	gcc main.o course.o student.o lab.o user.o stimer.o -o a.out -pthread

main.o: main.c
	gcc -c main.c

course.o: course.c
	gcc -c course.c

student.o:student.c
	gcc -c student.c

lab.o : lab.c
	gcc -c lab.c

user.o: user.c
	gcc -c user.c

stimer.o:stimer.c
	gcc -c stimer.c

clean:
	rm *.o
