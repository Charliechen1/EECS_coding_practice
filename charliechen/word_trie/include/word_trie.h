#ifndef TRIE_WORD_TRIE_H
#define TRIE_WORD_TRIE_H

#include <string>
#include <stdint.h>
#include <ul_sign.h>
#include <unordered_map>
#include <cmath>
#include "str_util.h"
#include <set>

namespace trie {

#define DEFINE_NORMAL_ATTRIBUTE(type, name)                 \
private:                                                    \
    type _##name;                                           \
public:                                                     \
    type get_##name() const { return _##name; }             \
    void set_##name(type value) { _##name = value; }

#define DEFINE_MAP_ATTRIBUTE(keytype, valtype, name)                       \
private:                                                                   \
    std::unordered_map<keytype, valtype> _##name;                          \
public:                                                                    \
    typedef std::unordered_map<keytype, valtype>::iterator name##_iterator;\
    name##_iterator name##_begin() { return _##name.begin(); }             \
    name##_iterator name##_end() { return _##name.end(); }                 \
    bool has_##name(keytype key) {                                         \
        return _##name.find(key) != name##_end();                          \
    }                                                                      \
    void set_##name(keytype key, valtype val) { _##name[key] = val; }      \
    valtype get_##name(keytype key) {                                      \
        if (!has_##name(key)) {                                            \
            return nullptr;                                                \
        }                                                                  \
        return _##name[key];                                               \
    }                                                                      \
    size_t name##_size() { return _##name.size(); }
    
class WordNode {
public:
    WordNode(bool is_tail = true, WordNode* parent = nullptr)
        :_is_tail(is_tail), 
         _parent(parent), 
         _children() 
    {}

    ~WordNode() {
        printf("deleteing node\n");
        if (_parent) {
            _parent = nullptr;
        }
        if (children_size()) {
            for (auto chd_it=children_begin(); 
                 chd_it!=children_end(); 
                 chd_it++) {
                delete chd_it->second;
            }
        }
        _children.clear();
    }
    WordNode* add_node(const std::wstring& w_blackword);
private:
    const static uint16_t STEP_LEN = 1;
    // 判断该node是否为blackword的结尾
    DEFINE_NORMAL_ATTRIBUTE(bool, is_tail);
    DEFINE_NORMAL_ATTRIBUTE(WordNode*, parent);
    // 这里考虑过是用明文还是sign作为key
    // 因为sign是int64需要8个bytes而这里的wstring有效长度仅为1,
    // 故使用明文作为key
    DEFINE_MAP_ATTRIBUTE(std::wstring, WordNode*, children);
};

class WordTrie {
public:
    WordTrie() {}
    ~WordTrie() {
        printf("deleting trie\n");
        if (_root) {
            delete _root;
        }
    }
    
    int init () {
        _root = new(std::nothrow) WordNode;
        if (!_root) {
            return -1;
        }
        return 0;
    }

    void clear () {
    }

    // 将blackword插入trie
    WordNode* add_node (const std::string& blackword);
    // 判断某word是否命中了blackword，即某词包含某个blackword
    bool is_match (const std::string& word);

private:
    DEFINE_NORMAL_ATTRIBUTE(WordNode*, root);
};

static inline uint64_t word_sign(const char* word) {
unsigned int low = 0;
    unsigned int high = 0;
    if (creat_sign_fs64(word, strlen(word), &high, &low) < 0) {
        return 0;
    }
    uint64_t sign = high;
    sign = (sign << 32) | low;
    return sign;
}

} // namespace trie 

#endif
