objects: build/angle.o

build/angle.o: build src/angle.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/angle.o -c src/angle.cpp

test: build
	g++ -Iinclude -std=c++11 -Wall -o build/test.o -c src/test.cpp

build:
	mkdir -p build
