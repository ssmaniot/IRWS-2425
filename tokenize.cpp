#include <algorithm>
#include <fstream>

#include "dictionary.hpp"
#include "utils.hpp"

// Store documents as (TermId, TF) pairs
// using TermId_t = uint32_t;
// using Document_t = std::vector<std::pair<TermId_t, int>>;

using DocPair_t = Document_t::value_type;

void add_token(Document_t& doc, Dictionary& dict, const std::string& token) {
  if (!dict.contains(token)) {
    dict.add(token);
  }
  TermId_t tokenId = dict[token];
  auto it = std::find_if(doc.begin(), doc.end(),
      [&tokenId](const DocPair_t& p) -> bool {
      return p.first == tokenId;
      });
  if (it != doc.end()) {
    it->second += 1;
  } else {
    doc.emplace_back(tokenId, 1);
  }
}

Document_t tokenize(Dictionary& dict, const std::string& file_path) {
  std::ifstream is{file_path};
  if (!is.is_open()) {
    throw std::runtime_error("ERROR: could not open '" + file_path + "'");
  }
  is >> std::noskipws;
  Document_t doc{};
  unsigned char ch{};
  std::string token{};
  while (is >> ch) {
    if (std::isspace(ch)) {
      if (!token.empty()) {
        add_token(doc, dict, token);
        token.clear();
      }
      continue;
    }
    token.push_back(ch);
  }
  if (!token.empty()) {
    add_token(doc, dict, token);
  }
  std::sort(doc.begin(), doc.end(), [](const DocPair_t& p1, const DocPair_t& p2) -> bool {
      return p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second);
      });
  return doc;
}
