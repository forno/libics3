test: bin build bin/test

OBJS = build/test.o build/angle.o build/parameter.o build/eepparam.o build/eeprom.o

bin/test: $(OBJS)
	g++ -o bin/test $(OBJS)

build/angle.o: src/angle.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/angle.o -c src/angle.cpp

build/parameter.o: src/parameter.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/parameter.o -c src/parameter.cpp

build/eepparam.o: src/eepparam.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/eepparam.o -c src/eepparam.cpp

build/eeprom.o: src/eeprom.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/eeprom.o -c src/eeprom.cpp

build/test.o: src/test.cpp
	g++ -Iinclude -std=c++11 -Wall -o build/test.o -c src/test.cpp

build:
	mkdir -p build

bin:
	mkdir -p bin
