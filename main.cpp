#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "dictionary.hpp"
#include "tokenize.hpp"

int main(int argc, const char **argv) {
  if (argc < 2) {
    std::cout << argv[0] << ": no argument provided.\n";
    return 0;
  }

  Dictionary dictionary{};
  for (int i=1; i<argc; ++i) {
    std::string file_name{argv[i]};
    std::cout << "Tokenizing '" << file_name << "'...\n";
    try {
      Document_t doc = tokenize(dictionary, file_name);
      std::cout << "Extracted following doc: [";
      for (std::size_t j=0; j<doc.size(); ++j) {
        const auto&[termId, count] = doc[j];
        std::cout << termId << ": " << count << ((j+1 != doc.size()) ? ", " : "]\n");
      }
    } catch (const std::runtime_error& e) {
      std::cout << e.what() << '\n';
    }
  }
}
