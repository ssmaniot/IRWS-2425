#include "tokenize.hpp"
#include "dictionary.hpp"
#include "utils.hpp"
#include <algorithm>
#include <fstream>
#include <unordered_map>

using DocPair_t = Document_t::value_type;
using FreqCounter_t = std::unordered_map<DocId_t, int>;

void add_token(FreqCounter_t &freq_counter, Dictionary &dict,
               const std::string &token) {
  TermId_t tokenId{};
  if (!dict.contains(token)) {

    tokenId = dict.add(token);
  } else {
    tokenId = dict[token];
  }
  auto it = std::find_if(
      freq_counter.begin(), freq_counter.end(),
      [&tokenId](const DocPair_t &p) -> bool { return p.first == tokenId; });
  if (it != freq_counter.end()) {
    it->second++;
  } else {
    freq_counter.emplace(tokenId, 1);
  }
}

Document_t tokenize(Dictionary &dict, const std::string &file_path) {
  std::ifstream is{file_path};
  if (!is.is_open()) {
    throw std::runtime_error("ERROR: could not open '" + file_path + "'");
  }
  is >> std::noskipws;
  Document_t doc{};
  FreqCounter_t freq_counter{};
  int num_terms = 0;
  unsigned char ch{};
  std::string token{};
  while (is >> ch) {
    if (std::isspace(ch)) {
      if (!token.empty()) {
        add_token(freq_counter, dict, token);
        ++num_terms;
        token.clear();
      }
      continue;
    }
    token.push_back(ch);
  }
  if (!token.empty()) {
    add_token(freq_counter, dict, token);
    ++num_terms;
  }
  for (const auto &[termId, count] : freq_counter) {
    float termFrequency =
        static_cast<float>(count) / static_cast<float>(num_terms);
    doc.emplace_back(termId, termFrequency);
  }
  std::sort(doc.begin(), doc.end(),
            [](const DocPair_t &p1, const DocPair_t &p2) -> bool {
              return p1.first < p2.first ||
                     (p1.first == p2.first && p1.second < p2.second);
            });
  return doc;
}
