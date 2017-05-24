CC=g++

main: functions.cpp main.cpp
	g++ functions.cpp -c
	g++ main.cpp functions.o -o main -std=c++11 -pthread
