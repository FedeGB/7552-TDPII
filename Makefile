all: Program Test
Program:
	g++ -c mainTest.cpp
	g++ -o main mainTest.o
Test:
	g++ -std=c++11 -c googleTest.cpp -I"./include"
	g++ -o gTest googleTest.o -L./lib -lgtest -lz -lpthread -lrt
Travis:
	g++-4.8 -std=c++11 -c googleTest.cpp -I"./include"
	g++-4.8 -o gTest googleTest.o -L./lib -lgtest -lz -lpthread -lrt
