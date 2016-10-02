CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra -Winit-self -Wno-missing-field-initializers
OBJS = build/test.o build/angle.o build/parameter.o build/eepparam.o build/eeprom.o

test: bin build bin/test

bin/test: $(OBJS)
	$(CXX) -o $@ $^

build/angle.o: src/angle.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

build/parameter.o: src/parameter.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

build/eepparam.o: src/eepparam.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

build/eeprom.o: src/eeprom.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

build/test.o: src/test.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

build:
	mkdir -p build

bin:
	mkdir -p bin
