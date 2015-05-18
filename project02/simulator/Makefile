CXX = g++
CXXFLAGS = -c

all: simulator

debug: CXXFLAGS += -g
debug: simulator
 
simulator:IOfunction.o main.o interpreter.o \
			getins.o execute.o simulator.o \
			error.o testbench.o RType.o \
			alloc.o IType.o stage.o \
			report.o translate.o
	$(CXX) -o pipeline \
	interpreter.o getins.o \
	IOfunction.o testbench.o \
	execute.o simulator.o \
	error.o alloc.o RType.o IType.o \
	stage.o translate.o report.o main.o



test.o:
	$(CXX) $(CXXFLAGS) test.cpp

main.o:
	$(CXX) $(CXXFLAGS) main.cpp

interpreter.o:
	$(CXX) $(CXXFLAGS) interpreter.cpp

simulator.o:
	$(CXX) $(CXXFLAGS) simulator.cpp

IOfunction.o:
	$(CXX) $(CXXFLAGS) IOfunction.cpp

getins.o:
	$(CXX) $(CXXFLAGS) getins.cpp

execute.o:
	$(CXX) $(CXXFLAGS) execute.cpp

testbench.o:
	$(CXX) $(CXXFLAGS) testbench.cpp

RType.o:
	$(CXX) $(CXXFLAGS) RType.cpp

IType.o:
	$(CXX) $(CXXFLAGS) IType.cpp

error.o:
	$(CXX) $(CXXFLAGS) error.cpp

alloc.o:
	$(CXX) $(CXXFLAGS) alloc.cpp

stage.o:
	$(CXX) $(CXXFLAGS) stage.cpp

report.o:
	$(CXX) $(CXXFLAGS) report.cpp

translate.o:
	$(CXX) $(CXXFLAGS) translate.cpp

clean:
	rm *.o debug pipeline test *.rpt *.bin
