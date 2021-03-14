//
// Given a binary search tree and a lowwer and upper limit, calculate the
// sum of all numbers in the tree within this limit
//

#include <iostream>
#include <functional>

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
TreeNode* createTree1() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right = new TreeNode(15);
    root->right->right = new TreeNode(18);
    return root;
}

TreeNode* createTree2() {
    TreeNode* root = new TreeNode(15);
    root->left = new TreeNode(9);
    root->right = new TreeNode(21);
    root->left->left = new TreeNode(7);
    root->left->right = new TreeNode(13);
    root->right->left = new TreeNode(19);
    root->right->right = new TreeNode(23);
    root->left->left->left = new TreeNode(5);
    root->left->right->left = new TreeNode(11);
    root->right->left->left = new TreeNode(17);
    return root;
}

TreeNode* createTree3() {
    TreeNode* root = new TreeNode(25);
    root->left = new TreeNode(16);
    root->right = new TreeNode(34);
    root->left->left = new TreeNode(13);
    root->left->right = new TreeNode(22);
    root->right->left = new TreeNode(31);
    root->right->right = new TreeNode(37);
    root->left->left->left = new TreeNode(10);
    root->left->right->left = new TreeNode(19);
    root->right->left->left = new TreeNode(28);
    return root;
}

class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        int sum = 0;
        if (root->val >= low && root->val <= high) {
            // We need to traverse both sides of tree
            traverse(root->left, low, high, sum);
            sum += root->val;
            traverse(root->right, low, high, sum);
        } else if (root->val >= low) {
            // We need to traverse left side of tree
            traverse(root->left, low, high, sum);
        } else {
            // We need to traverse right side of tree
            traverse(root->right, low, high, sum);
        }
        return sum;
    }
    
private:
    void traverse(TreeNode* node, int low, int high, int& sum)
    {
        if (node) {
            if (node->val >= low && node->val <= high) {
                sum += node->val;
                if (node->val == low) {
                    traverse(node->right, low, high, sum);
                } else if (node->val == high) {
                    traverse(node->left, low, high, sum);
                } else {
                    if (node->left && node->left->val >= low)
                        traverse(node->left, low, high, sum);
                    if (node->right && node->right->val <= high)
                        traverse(node->right, low, high, sum);
                }
            } else if (node->val >= low) {
                // stay on the left
                traverse(node->left, low, high, sum);
            } else {
                // stay on the right
                traverse(node->right, low, high, sum);
            }
            
        }
    }
};

void cleanuptree(TreeNode*& root)
{
    if (root) {
        cleanuptree(root->left);
        cleanuptree(root->right);
        delete root;
        root = nullptr;
    }
}

int main(int argc, const char * argv[]) {
    TreeNode* tree1 = createTree1();
    TreeNode* tree2 = createTree2();
    TreeNode* tree3 = createTree3();
    Solution obj;
    std::cout << "Sum in tree 1: " << obj.rangeSumBST(tree1, 7, 15) << std::endl;
    std::cout << "Sum in tree 2: " << obj.rangeSumBST(tree2, 19, 21) << std::endl;
    std::cout << "Sum in tree 3: " << obj.rangeSumBST(tree3, 22, 37) << std::endl;
    cleanuptree(tree1);
    cleanuptree(tree2);
    cleanuptree(tree3);
    return 0;
}

