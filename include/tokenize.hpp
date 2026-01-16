#pragma once

#include "dictionary.hpp"
#include "utils.hpp"
#include <string>

Document_t tokenize(Dictionary &dict, const std::string &file_path);
