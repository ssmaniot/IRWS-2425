#include <stdexcept>
#include "dictionary.hpp"

Dictionary::Dictionary() noexcept: _data{}, _nextId{} {}

bool Dictionary::contains(const std::string& word) const noexcept {
  return _data.find(word) != _data.end();
}

TermId_t Dictionary::add(const std::string& word) noexcept {
  TermId_t newId = _nextId++;
  _data.insert(std::pair<std::string, TermId_t>{word, newId});
  return newId;
}

TermId_t Dictionary::operator[](const std::string& word) const {
  auto it = _data.find(word);
  if (it == _data.end()) {
    throw std::runtime_error("ERROR: word '" + word + "' not in dictionary.");
  }
  return it->second;
}
