#pragma once

#include <cstdint>
#include <vector>

using TermId_t = uint32_t;

// Store documents as vector of (TermId, TF) pairs
using DocId_t = uint32_t;
using Document_t = std::vector<std::pair<TermId_t, int>>;
