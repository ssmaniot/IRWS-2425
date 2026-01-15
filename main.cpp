#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "utils.hpp"

int main(int argc, const char **argv) {
  if (argc < 2) {
    std::cout << argv[0] << ": no argument provided.\n";
    return 0;
  }

  for (int i=1; i<argc; ++i) {
    std::string file_name{argv[i]};
    std::cout << "Tokenizing '" << file_name << "'...\n";
    try {
      std::vector<std::string> tokens = tokenize(file_name);
      std::cout << "Extracted following tokens: [";
      for (std::size_t j=0; j<tokens.size(); ++j) {
        std::cout << tokens[j] << ((j+1 != tokens.size()) ? ", " : "]\n");
      }
    } catch (const std::runtime_error& e) {
      std::cout << e.what() << '\n';
    }
  }
}
