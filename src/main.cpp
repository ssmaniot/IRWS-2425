#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "corpus.hpp"
#include "dictionary.hpp"
#include "tokenize.hpp"

int main(int argc, const char **argv) {
  if (argc < 2) {
    std::cout << argv[0] << ": no argument provided.\n";
    return 0;
  }

  Dictionary dictionary{};
  Corpus corpus{};
  std::vector<DocId_t> docIds{};
  for (int i=1; i<argc; ++i) {
    std::string file_name{argv[i]};
    std::cout << "Tokenizing '" << file_name << "'...\n";
    try {
      Document_t doc = tokenize(dictionary, file_name);
      DocId_t id = corpus.add(std::move(doc));
      docIds.push_back(id);
    } catch (const std::runtime_error& e) {
      std::cout << e.what() << '\n';
    }
  }
  std::cout << "\nDocuments:\n\n";
  for (const auto& id : docIds) {
    const Document_t &doc_ref = corpus[id];
    std::cout << "doc_id[" << id << "]: [";
    for (std::size_t j=0; j<doc_ref.size(); ++j) {
      const auto&[termId, count] = doc_ref[j];
      std::cout << termId << ": " << count << ((j+1 != doc_ref.size()) ? ", " : "]\n\n");
    }
  }
}
