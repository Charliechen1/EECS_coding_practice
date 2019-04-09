#ifndef TRIE_STR_UTIL_H
#define TRIE_STR_UTIL_H

#include <cstdlib>
#include <string>

namespace trie {

std::wstring s2ws(const std::string& str);

std::string ws2s(const std::wstring& w_str);

}// namespace trie
#endif
