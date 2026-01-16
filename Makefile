CXX      := g++
CXXFLAGS := -std=c++20 -pedantic -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer
TARGET   := main
SRC      := main.cpp corpus.cpp tokenize.cpp dictionary.cpp
#
# Output directory for object and dependency files
BUILDDIR := build

# Derived lists
OBJ := $(SRC:%.cpp=$(BUILDDIR)/%.o)
DEP := $(OBJ:.o=.d)

.PHONY: all clean

all: $(TARGET)

# Link step
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# Compile step (+ auto header deps)
# -MMD: write dependencies excluding system headers
# -MP : add phony targets for headers (avoids errors if headers are removed)
$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Ensure build directory exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Include generated dependency files if they exist
-include $(DEP)

clean:
	rm -rf $(BUILDDIR) $(TARGET)
