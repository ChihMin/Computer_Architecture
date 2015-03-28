simulator:IOfunction.o main.o interpreter.o getins.o execute.o simulator.o
	g++ -o single_cycle interpreter.o getins.o IOfunction.o execute.o simulator.o main.o

debug:interpreter.o IOfunction.o getins.o simulator.o main.o execute.o
	g++ -g -o debug IOfunction.o interpreter.o getins.o execute.o simulator.o  main.o

main.o:
	g++ -c main.cpp

interpreter.o:
	g++ -c interpreter.cpp

simulator.o:
	g++ -c simulator.cpp

IOfunction.o:
	g++ -c IOfunction.cpp

getins.o:
	g++ -c getins.cpp

execute.o:
	g++ -c execute.cpp

clean:
	rm *.o single_cycle debug
