#include <stdexcept>
#include <string>
#include "corpus.hpp"

Corpus::Corpus() noexcept: _data{}, _nextId{} {}

bool Corpus::contains(DocId_t docId) const noexcept {
  return _data.find(docId) != _data.end();
}

DocId_t Corpus::add(Document_t&& doc) noexcept {
  TermId_t newId = _nextId++;
  _data.emplace(newId, std::forward<Document_t>(doc));
  return newId;
}

const Document_t& Corpus::operator[](DocId_t docId) const {
  auto it = _data.find(docId);
  if (it == _data.end()) {
    throw std::runtime_error("ERROR: docId " + std::to_string(docId) + " not in dictionary.");
  }
  return it->second;
}
