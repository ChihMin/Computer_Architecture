simulator:IOfunction.o main.o interpreter.o \
			getins.o execute.o simulator.o \
			error.o testbench.o RType.o \
			alloc.o IType.o
	g++ -o CMP \
	interpreter.o getins.o \
	IOfunction.o testbench.o \
	execute.o simulator.o \
	error.o alloc.o RType.o IType.o main.o

test:IOfunction.o test.o interpreter.o \
			getins.o execute.o simulator.o \
			testbench.o RType.o
	g++ -o test \
	interpreter.o getins.o \
	IOfunction.o testbench.o \
	execute.o simulator.o \
	error.o alloc.o RType.o IType.o test.o

test.o:
	g++ -c test.cpp

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

testbench.o:
	g++ -c testbench.cpp

RType.o:
	g++ -c RType.cpp

IType.o:
	g++ -c IType.cpp

error.o:
	g++ -c error.cpp

alloc.o:
	g++ -c alloc.cpp

clean:
	rm *.o CMP test *.rpt *.bin
