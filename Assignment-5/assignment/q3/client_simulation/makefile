a.out: main.o client_sim.o 
	g++ main.o client_sim.o -o a.out

main.o : main.cpp
	g++ -c main.cpp

client_sim.o : client_sim.cpp
	g++ -c client_sim.cpp

clean:
	rm *.o
