#pragma once

#include "utils.hpp"
#include <string>
#include <unordered_map>

class Dictionary {
private:
  std::unordered_map<std::string, TermId_t> _data;
  TermId_t _nextId;

  using Node_t = decltype(_data)::node_type;
  using Iterator_t = decltype(_data)::const_iterator;

public:
  explicit Dictionary() noexcept;

  bool contains(const std::string &word) const noexcept;

  TermId_t add(const std::string &word) noexcept;

  TermId_t operator[](const std::string &word) const;

  Iterator_t begin() const { return _data.begin(); }
  Iterator_t end() const { return _data.end(); }
};
