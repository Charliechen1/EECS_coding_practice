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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root)   return root;
        // Iterative solution. Use the binary search tree property: left < parent < right
        bool goLeft = (p->val < root->val) && (q->val < root->val);
        bool goRight = (p->val > root->val) && (q->val > root->val);
        while(goLeft || goRight){
            root = (goLeft) ? root->left : root->right;
            goLeft = (p->val < root->val) && (q->val < root->val);
            goRight = (p->val > root->val) && (q->val > root->val);
        }
        return root;
    }
};
