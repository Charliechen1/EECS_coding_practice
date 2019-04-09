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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root)   return {};
        // USE A QUEUE FOR PER LEVEL PROCESSING
        queue<TreeNode*> todo;
        todo.push(root);
        vector<vector<int>> result;
        for(vector<int> level; !todo.empty(); level.clear()){   // for each level
            int n = todo.size();    // size of current queue is size of current level
            for(int i=0; i<n; i++){
                TreeNode* node = todo.front();
                todo.pop();
                level.push_back(node->val);
                if(node->left)  todo.push(node->left);
                if(node->right) todo.push(node->right);
            }
            if(level.size() >0) result.push_back(move(level));  // move for transfering, reuse space
        }
        return result;
    }
};
