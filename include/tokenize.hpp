#pragma once

#include "dictionary.hpp"
#include "utils.hpp"
#include <string>
#include <vector>

Document_t tokenize(Dictionary &dict, const std::string &file_path);
