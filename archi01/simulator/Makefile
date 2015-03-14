simulator:main.o interpreter.o simulator.o IOfunction.o
	g++ -o single_cycle interpreter.o main.o simulator.o IOfunction.o

main.o:
	g++ -c main.cpp

interpreter.o:
	g++ -c interpreter.cpp

simulator.o:
	g++ -c simulator.cpp

IOfunction.o:
	g++ -c IOfunction.cpp

clean:
	rm *.o single_cycle
