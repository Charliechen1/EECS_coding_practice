
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(!root)   return {};
        // Use a processing queue.
        queue<TreeNode*> todo;
        todo.push(root);
        TreeNode* curr = root;
        vector<vector<int>> result;
        bool reversed = false;
        for(vector<int> level; !todo.empty(); level.clear()){   // per level processing
            int n = todo.size();
            level.resize(n);
            for(int i=0; i<n; ++i){
                TreeNode* node = todo.front();
                todo.pop();
                int index = (reversed) ? (n-1-i) : i;           // know size therefore know reverse index
                level[index] = node->val;
                if(node->left)  todo.push(node->left);
                if(node->right) todo.push(node->right);
            }
            result.push_back(move(level));
            reversed = !reversed;
        }
        return result;
    }
};
