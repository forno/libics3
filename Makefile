test: bin/test

bin/test: bin build/test.o build/angle.o
	g++ -o bin/test build/test.o build/angle.o

build/angle.o: build src/angle.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/angle.o -c src/angle.cpp

build/test.o: build src/test.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/test.o -c src/test.cpp

build:
	mkdir -p build

bin:
	mkdir -p bin
