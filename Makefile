CC=g++

main: functions.cpp main.cpp
	g++ functions.cpp -c -std=c++11 -pthread
	g++ main.cpp functions.o -o main -std=c++11 -pthread
