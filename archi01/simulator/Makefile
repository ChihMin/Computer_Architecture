simulator:IOfunction.o main.o interpreter.o simulator.o
	g++ -o single_cycle interpreter.o IOfunction.o simulator.o main.o 


debug:interpreter.o IOfunction.o simulator.o main.o
	clang++ -g -o debug IOfunction.o interpreter.o simulator.o main.o

main.o:
	g++ -c main.cpp

interpreter.o:
	g++ -c interpreter.cpp

simulator.o:
	g++ -c simulator.cpp

IOfunction.o:
	g++ -c IOfunction.cpp

clean:
	rm *.o single_cycle debug
