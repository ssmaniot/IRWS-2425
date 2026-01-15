CXX      := g++
CXXFLAGS := -std=c++20 -pedantic -Wall -Wextra
TARGET   := main
SRC      := main.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
