#include "word_trie.h"

namespace trie {
    
WordNode* WordTrie::add_node (const std::string& blackword) { 
    auto w_blackword = s2ws(blackword);
    if (!_root) {
        return nullptr;
    }
    WordNode* p_sn = _root->add_node(w_blackword);
    return p_sn;
}

bool WordTrie::is_match (const std::string& word) {
    if (_root == nullptr) {
        return false;
    }
    // start searching on the built trie
    auto w_word = s2ws(word);
    // initialze the queue for each search
    std::set<WordNode*> cur_act_nodes;
    cur_act_nodes.insert(_root);
    for (size_t char_idx=0; char_idx<w_word.size(); ++char_idx) {
        auto w_char_str = w_word.substr(char_idx, 1);
        auto node_end_it = cur_act_nodes.end();
        for (auto sn_it=cur_act_nodes.begin(); 
             sn_it!=node_end_it;
             ++sn_it) {
            auto cur_node = *sn_it;
            // 记录目前扫到的node
            cur_act_nodes.insert(cur_node);
            if (cur_node->has_children(w_char_str)) {
                auto chd_node = cur_node->get_children(w_char_str);
                // 如果当前扫到的node为tail，那么我们认为title包含敏感词
                // 反之，该node加入扫描对象
                if (chd_node->get_is_tail()) {
                    return true;
                } else {
                    cur_act_nodes.insert(chd_node);
                }
            } 
        }
    }
 
    return false;
}

WordNode* WordNode::add_node (const std::wstring& w_blackword) {
    uint16_t bw_size = w_blackword.size();

    bool is_tail = bw_size <= STEP_LEN;
    uint16_t cur_step_len = is_tail ? bw_size : STEP_LEN;
    std::wstring w_head = w_blackword.substr(0, cur_step_len);
    std::wstring w_tail = w_blackword.substr(
        cur_step_len, bw_size - cur_step_len);
    WordNode* p_wn = nullptr;
    if (this->has_children(w_head)) {
        // 如果目前这个字已经存在
        p_wn = this->get_children(w_head);
        if (is_tail) {
            // 且这个字已经是最后一个
            return p_wn;
        }
    } else {
        p_wn = new(std::nothrow) WordNode(is_tail, this);
        this->set_children(w_head, p_wn); 
    }
    if (w_tail.size() > 0){  
        return p_wn->add_node(w_tail);
    } 
    return this;
}

} // namespace trie
