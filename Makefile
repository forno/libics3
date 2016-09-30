test:
	mkdir -p build
	g++ -Iinclude -std=c++11 -Wall -o build/test.o -c src/test.cpp
