#include "utils.hpp"

#include <fstream>

std::vector<std::string> tokenize(const std::string& file_path) {
  std::vector<std::string> tokens{};
  if (std::ifstream is{file_path}; is.is_open()) {
    is >> std::noskipws;
    unsigned char ch{};
    std::string token{};
    while (is >> ch) {
      if (std::isspace(ch)) {
        if (!token.empty()) {
          tokens.push_back(token);
          token.clear();
        }
        continue;
      }
      token.push_back(ch);
    }
    if (!token.empty()) {
      tokens.push_back(token);
    }
  } else {
    throw std::runtime_error("ERROR: could not open '" + file_path + "'");
  }
  return tokens;
}
