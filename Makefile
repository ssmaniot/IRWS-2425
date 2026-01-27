CXX      := g++
CXXFLAGS := -std=c++20 -O3 -march=native -pedantic -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer -Iinclude
TARGET   := main

SRCDIR   := src

# Output directory for object and dependency files
BUILDDIR := build

# Source files
SRC := $(wildcard $(SRCDIR)/*.cpp)

# Derived lists
OBJ := $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
DEP := $(OBJ:.o=.d)

.PHONY: all clean compdb

all: $(TARGET)

compdb:
	bear -- make clean all

# Link step
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# Compile step (+ auto header deps)
# -MMD: write dependencies excluding system headers
# -MP : add phony targets for headers (avoids errors if headers are removed)
# Ensure build directory exists
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include generated dependency files if they exist
-include $(DEP)

clean:
	rm -rf $(BUILDDIR) $(TARGET)
