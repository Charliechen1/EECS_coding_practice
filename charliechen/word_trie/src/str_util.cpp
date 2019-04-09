#include "str_util.h"

namespace trie {

std::wstring s2ws(const std::string& str) {
    if (str.empty()) {
        return L"";
    }
    unsigned len = str.size() + 1;
    setlocale(LC_CTYPE, "en_US.UTF-8");
    wchar_t *p = new wchar_t[len];
    mbstowcs(p, str.c_str(), len);
    std::wstring w_str(p);
    delete[] p;
    return w_str;
}

std::string ws2s(const std::wstring& w_str) {
    if (w_str.empty()) {
        return "";
    }
    unsigned len = w_str.size() * 4 + 1;
    setlocale(LC_CTYPE, "en_US.UTF-8");
    char *p = new char[len];
    wcstombs(p, w_str.c_str(), len);
    std::string str(p);
    delete[] p;
    return str;
}

}// namespace trie 
