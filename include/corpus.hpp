#pragma once

#include "utils.hpp"
#include <algorithm>
#include <unordered_map>

class Corpus {
private:
  std::unordered_map<DocId_t, Document_t> _data;
  DocId_t _nextId;

  using Node_t = decltype(_data)::node_type;
  using Iterator_t = decltype(_data)::const_iterator;

public:
  explicit Corpus() noexcept;

  bool contains(DocId_t docId) const noexcept;

  DocId_t add(Document_t &&doc) noexcept;

  const Document_t &operator[](DocId_t docId) const;

  int size() const noexcept { return _data.size(); }

  int count_docs(TermId_t id) const noexcept {
    return std::count_if(_data.begin(), _data.end(),
                         [id](const auto &it) -> bool {
                           const Document_t &doc = it.second;
                           return std::find_if(doc.begin(), doc.end(),
                                               [id](const auto &term_tf) {
                                                 return term_tf.first == id;
                                               }) != doc.end();
                         });
  }

  Iterator_t begin() const { return _data.begin(); }

  Iterator_t end() const { return _data.end(); }
};
