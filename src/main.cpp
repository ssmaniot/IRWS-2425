#include "corpus.hpp"
#include "dictionary.hpp"
#include "tokenize.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
#include <unordered_map>

int main(int argc, const char **argv) {
  if (argc < 2) {
    std::cout << argv[0] << ": no argument provided.\n";
    return 0;
  }

  Dictionary dictionary{};
  Corpus corpus{};
  std::vector<DocId_t> docIds{};

  // Tokenize documents
  for (int i = 1; i < argc; ++i) {
    std::string file_name{argv[i]};
    std::cout << "Tokenizing '" << file_name << "'...\n";
    try {
      Document_t doc = tokenize(dictionary, file_name);
      DocId_t id = corpus.add(std::move(doc));
      docIds.push_back(id);
    } catch (const std::runtime_error &e) {
      std::cout << e.what() << '\n';
    }
  }
  std::cout << "\nDocuments:\n\n";
  for (const auto &id : docIds) {
    const Document_t &doc_ref = corpus[id];
    std::cout << "doc_id[" << id << "]: [";
    for (std::size_t j = 0; j < doc_ref.size(); ++j) {
      const auto &[termId, count] = doc_ref[j];
      std::cout << termId << ": " << count
                << ((j + 1 != doc_ref.size()) ? ", " : "]\n\n");
    }
  }

  // Compute IDF
  std::unordered_map<TermId_t, float> idf{};
  float num_total_documents = static_cast<float>(corpus.size());
  for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
    TermId_t id = it->second;
    int num_documents_with_term = corpus.count_docs(id);
    idf[id] = std::log(num_total_documents / num_documents_with_term);
  }

  // Compute TF-IDF
  std::map<std::pair<TermId_t, DocId_t>, float> tfidf{};
  for (const auto &[doc_id, doc] : corpus) {
    for (const auto &[term_id, freq] : doc) {
      const auto [it, succ] =
          tfidf.emplace(std::make_pair(term_id, doc_id), freq / idf[term_id]);
      std::cout << "tfidf[" << term_id << ";" << doc_id << "] = " << it->second
                << "\n";
    }
  }
  return 0;
}
