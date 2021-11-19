a.out: main.o server_sim.o
	g++ main.o server_sim.o -o a.out -pthread

main.o : main.cpp
	g++ -c main.cpp

server_sim.o : server_sim.cpp
	g++ -c server_sim.cpp

clean:
	rm *.o
