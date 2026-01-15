CXX      := g++
CXXFLAGS := -std=c++20 -pedantic -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer
TARGET   := main
SRC      := main.cpp tokenize.cpp dictionary.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

clean:
	rm -f $(TARGET)
