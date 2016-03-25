all: Test
Test:
	$(CXX) -std=c++11 -c googleTest.cpp -I"./include"
	$(CXX) -o gTest googleTest.o -L./lib -lgtest -lz -lpthread -lrt

