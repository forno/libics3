test: bin/test

bin/test: bin build/test.o build/angle.o build/parameter.o build/eepparam.o
	g++ -o bin/test build/test.o build/angle.o build/parameter.o

build/angle.o: build src/angle.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/angle.o -c src/angle.cpp

build/parameter.o: build src/parameter.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/parameter.o -c src/parameter.cpp

build/eepparam.o: build src/eepparam.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/eepparam.o -c src/eepparam.cpp

build/test.o: build src/test.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/test.o -c src/test.cpp

build:
	mkdir -p build

bin:
	mkdir -p bin
