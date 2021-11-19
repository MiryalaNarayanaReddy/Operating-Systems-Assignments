a.out: main.o client_sim.o stimer.o 
	g++ main.o client_sim.o stimer.o -o a.out -pthread

main.o : main.cpp
	g++ -c main.cpp

client_sim.o : client_sim.cpp
	g++ -c client_sim.cpp

stimer.o : stimer.cpp
	g++ -c stimer.cpp

clean:
	rm *.o
