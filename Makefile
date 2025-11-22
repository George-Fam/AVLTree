CXXFLAGS = -std=c++11 -O2
CXXFLAGS_DEBUG = -std=c++11 -g -O0 -Wall -Wextra -pedantic
TARGET = test
SRC = testtp3.cpp
DEPS = arbreavl.h pile.h

.PHONY: all run debug clean

all: $(TARGET)

$(TARGET): $(SRC) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug:
	$(CXX) $(CXXFLAGS_DEBUG) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)