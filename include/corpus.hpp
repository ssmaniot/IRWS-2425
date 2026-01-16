#pragma once

#include "utils.hpp"
#include <unordered_map>

class Corpus {
public:
  explicit Corpus() noexcept;

  bool contains(DocId_t docId) const noexcept;

  DocId_t add(Document_t &&doc) noexcept;

  const Document_t &operator[](DocId_t docId) const;

private:
  std::unordered_map<DocId_t, Document_t> _data;
  DocId_t _nextId;

  using Node_t = decltype(_data)::node_type;
};
