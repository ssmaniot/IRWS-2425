#pragma once

#include <string>
#include <unordered_map>
#include "utils.hpp"

class Dictionary {
  public:
    explicit Dictionary() noexcept; 

    bool contains(const std::string& word) const noexcept; 

    TermId_t add(const std::string& word) noexcept;

    TermId_t operator[](const std::string& word) const; 

  private:
    std::unordered_map<std::string, TermId_t> _data;
    TermId_t _nextId;

    using Node_t = decltype(_data)::node_type;
};
