CC=g++

main: functions.cpp main.cpp poem.cpp
	g++ poem.cpp -c -std=c++11
	g++ functions.cpp -c -std=c++11 -pthread
	g++ main.cpp functions.o  poem.o -o p2p -std=c++11 -pthread
