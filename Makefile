prog=test.l
main: main.cpp headers/utils.hpp
	g++ -O3 -o bin/main main.cpp
run: main
	./bin/main $(prog)