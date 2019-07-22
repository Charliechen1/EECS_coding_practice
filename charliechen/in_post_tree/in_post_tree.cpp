/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
*/
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return buildTreeHelper(inorder, postorder, 0, inorder.size(), 0, postorder.size());
}

TreeNode* buildTreeHelper(vector<int>& inorder, vector<int>& postorder, 
                          uint32_t in_st, uint32_t in_ed, uint32_t po_st, uint32_t po_ed)
{
    TreeNode *res = NULL;
    if (in_ed <= in_st || 
        po_ed <= po_st || 
        in_ed - in_st != po_ed - po_st) 
    {
        return res;
    }
    // find out the middle one
    int mid = postorder[po_ed - 1];
    res = new TreeNode(mid);
    uint32_t mid_in_idx = 0;
    for (uint32_t i=0; i<inorder.size(); i++) {
        if (inorder[i] == mid) {
            mid_in_idx = i;
            break;
        }
    }
    // subtree inorder index
    uint32_t l_in_st = in_st;
    uint32_t l_in_ed = mid_in_idx;
    uint32_t r_in_st = mid_in_idx + 1;
    uint32_t r_in_ed = in_ed;
    
    // subtree postorder index
    uint32_t sub_size = mid_in_idx - l_in_st;
    
    uint32_t l_po_st = po_st;
    uint32_t l_po_ed = po_st + sub_size;
    uint32_t r_po_st = po_st + sub_size;
    uint32_t r_po_ed = po_ed - 1;
    
    res->left = buildTreeHelper(inorder, postorder, l_in_st, l_in_ed, l_po_st, l_po_ed);
    res->right = buildTreeHelper(inorder, postorder, r_in_st, r_in_ed, r_po_st, r_po_ed);
    return res;
}
