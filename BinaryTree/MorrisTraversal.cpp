// Definition for a binary tree node.
#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

// morris 法中序遍历
// 核心：用空的右指针作为临时线索
vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> res;
    TreeNode *cur = nullptr;
    while (root != nullptr) {
        cur = root->left;
        if (cur == nullptr) {         // cur结点不存在
            res.push_back(root->val); // root的值计入结果
            root = root->right;       // 向右
        } else {
            while (cur->right != nullptr && cur->right != root) {
                cur = cur->right;
            }
            if (cur->right ==
                nullptr) { // 右指针指向nullptr，说明需要连接至root
                cur->right = root;
                root = root->left;
            } else {                      // 右指针已经指向root，说明左子树已经访问完毕，下一步需要访问右子树
                res.push_back(root->val); // root的值计入结果
                cur->right = nullptr;     // 清空cur的右指针，恢复树的形状
                root = root->right;
            }
        }
    }
    return res;
}

// Morris法 前序遍历
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        TreeNode* cur = nullptr;
        while (root != nullptr) {
            
            cur = root->left;
            if (cur == nullptr) {
                res.push_back(root->val);
                root = root->right;
            } else {
                while (cur->right != nullptr && cur->right != root) {
                    cur = cur->right;
                }
                if (cur->right == nullptr) {
                    res.push_back(root->val);
                    cur->right = root;
                    root = root->left;
                } else {
                    root = root->right;
                    cur->right = nullptr;
                }
            }
        }
        return res;
    }