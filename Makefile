.PHONY:clean
clean:
	-rm tp1

.PHONY:all
all:
	-g++  tp1.cpp -o tp1 -O1 -Wall -pedantic 
