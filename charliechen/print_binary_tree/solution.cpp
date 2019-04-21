/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        int h = treeHeight(root);
        vector<vector<string>> res;
        for (int idx=0; idx<h; idx++) {
            vector<string> level;
            res.push_back(level);
        }
        if (root != nullptr){
            pushRes(root, 0, res, h);
        }
        return res;
    }
    
    int treeHeight (TreeNode* root) {
        if (root == nullptr) return 0;
        return max(treeHeight(root->left), treeHeight(root->right)) + 1;
    }
    
    void pushRes(TreeNode* root,const int& height, vector<vector<string>>& res, const int& max_h) {
        if (height == max_h) return;
        TreeNode* left = root==nullptr ? nullptr:root->left;
        TreeNode* right = root==nullptr ? nullptr:root->right;
        string val_s = root==nullptr ? "":to_string(root->val);

        pushRes(left, height+1, res, max_h);
        for (auto it=0; it<height; it++) {
            res[it].push_back("");
        }
        for (auto it=height+1; it<max_h; it++) {
            res[it].push_back("");
        }
        res[height].push_back(val_s);
        pushRes(right, height+1, res, max_h);
    }
};