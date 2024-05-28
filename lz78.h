#ifndef __LZ78_H__
#define __LZ78_H__
#include <vector>
#include <string>
#include <utility>


std::vector<std::pair<size_t, char>> lz78Encode(const std::string& text);
std::string lz78Decoder(const std::vector<std::pair<size_t, char>>& dictionary);
void printDictionary(const std::vector<std::pair<size_t, char>>& d);


#endif
