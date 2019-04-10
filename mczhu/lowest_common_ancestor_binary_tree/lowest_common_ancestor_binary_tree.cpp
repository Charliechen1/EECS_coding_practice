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
        if(!root || root == p || root == q)   return root;
        // Iterative solution. Use a hashmap to record parent child relationship
        unordered_map<TreeNode*, TreeNode*> parent; // store parent ralation <node, parent>
        parent[root] = NULL;
        stack<TreeNode*> st;                       // for processing
        st.push(root);
        
        while(!parent[p] || !parent[q]){            // searching until find parents for both p and q
            TreeNode* node = st.top();
            st.pop();
            if(node->right){
                parent[node->right] = node;
                st.push(node->right);
            }
            if(node->left){
                parent[node->left] = node;
                st.push(node->left);
            }
        }
        // Then use the hashmap to find lowest common ancestor for p&q
        set<TreeNode*> ancestors;
        while(p){
            ancestors.insert(p);
            p = parent[p];
        }
        while(ancestors.find(q) == ancestors.end()){
            q = parent[q];
        }
        return q;
    }
    // Side note: recursive solution is pretty straightforward
};
