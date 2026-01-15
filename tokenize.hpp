#pragma once

#include <string>
#include <vector>

#include "dictionary.hpp"
#include "utils.hpp"

Document_t tokenize(Dictionary& dict, const std::string& file_path);
