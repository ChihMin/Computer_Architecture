CC = g++
NAME = MOESI
SRC = $(NAME).cpp
FLAG = -std=c++11

debug: FLAG += -g
debug: all
	

all:
	$(CC) $(FLAG) $(SRC) -o $(NAME)

clean:
	rm $(NAME) *.txt
