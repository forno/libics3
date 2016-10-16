CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra -Winit-self -Wno-missing-field-initializers -Weffc++ -Winline -Wold-style-definition
OBJS = build/test.o build/angle.o build/parameter.o build/eepparam.o build/eeprom.o build/core.o build/id.o build/ics3.o

test: bin build bin/test

bin/test: $(OBJS)
	$(CXX) -o $@ $^

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

build:
	mkdir -p build

bin:
	mkdir -p bin
