//
// A complete binary tree is one in which every level, except possibly the last,
// is completely filled, and all nodes are as far left as possible.
// Check for complete binary tree - If we find a node that is not full (not a leaf or
//  does not contain two children), this means that the tree is not completely filled.
//  We need to ensure that this is the letf-most node. We can do this by processing trees
//  level-order (left to right) fashion, keeping track of non-full node and returning false
//  if the above condition is violated
//

#include <iostream>
#include <vector>
#include <queue>
#include <optional>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d, Node* l, Node* r) : data(d), left(l), right(r) { }
};

class Binarytree {
public:
    Binarytree() : root(nullptr) { }
    
    void create(const std::vector<std::optional<int>>& data) {
        std::queue<std::pair<Node*, int>> queue;
        queue.push(std::make_pair(new Node(data[0].value(), nullptr, nullptr), 0));
        
        while (!queue.empty())
        {
            Node* currNode = nullptr;
            int nodeidx = 0;
            std::tie(currNode, nodeidx) = queue.front();
            queue.pop();
            
            if (root == nullptr) {
                root = currNode;
            }
            
            int left_child_idx = 2*nodeidx + 1;
            int right_child_idx = 2*nodeidx + 2;
            
            if (left_child_idx < data.size() && data[left_child_idx].has_value())
            {
                currNode->left = new Node({data[left_child_idx].value(), nullptr, nullptr});
                queue.push({currNode->left, left_child_idx});
            }
            
            if (right_child_idx < data.size() && data[right_child_idx].has_value())
            {
                currNode->right = new Node({data[right_child_idx].value(), nullptr, nullptr});
                queue.push({currNode->right, right_child_idx});
            }
        }
    }
    
    /**
     * The timple complexity of the following solution is O(n) because we traverse the whole tree
     * The space complexity is O(n) because we store the elements in a queue. We can do better
     */
    bool isComplete_1() {
        std::queue<Node*> queue;
        queue.push(root);
        bool NonfullnodeEncountered = false;
        
        while (!queue.empty()) {
            Node* top = queue.front();
            queue.pop();
            // if we have encountered a non-full node, any subsequent
            // node should not have children in level-order traversal.
            if (NonfullnodeEncountered && (top->left || top->right))
                return false;
            
            if (isfullNode(top)) {
                if (top->left) {
                    queue.push(top->left);
                    queue.push(top->right);
                }
            } else {
                // Either not a leaf or only one child exists
                if (top->left == nullptr && top->right) {
                    // No left child, but right one exists => Break
                    return false;
                } else if (top->left) {
                    // Left exists and right does not
                    NonfullnodeEncountered = true;
                    queue.push(top->left);
                }
            }
        }
        
        return true;
    }
    
    /**
     * We create an array using the tree elements. Every node has a left child at index 2*i+1
     * and right child at index 2*i+2. For a complete tree, every position should be filled by a child
     * node. If there are any missing entries in between, then we don't have a complete tree.
     * We don't really need any array to keep track of the nodes. We just need to pass around an index
     * and validate it
     */
    bool isComplete_2() {
        return isCompleteHelper(root, 0, size(root));
    }
    
    ~Binarytree() {
        std::cout << "Destroying:  ";
        cleanup(root);
        std::cout << std::endl;
    }
    
private:
    
    int size(Node* root) {
        if (root == nullptr)
            return 0;
        
        return 1 + size(root->left) + size(root->right);
    }
    
    bool isCompleteHelper(Node* node, int indx, int sz) {
        if (node == nullptr) {
            return true;
        }
        
        if ((node->left && (2*indx+1 >= sz)) || !isCompleteHelper(node->left, 2*indx+1, sz))
            return false;
        
        if ((node->right && (2*indx+2 >= sz)) || !isCompleteHelper(node->right, 2*indx+2, sz))
            return false;
        
        return true;
    }
    
    void cleanup(Node*& r) {
        if (r) {
            cleanup(r->left);
            cleanup(r->right);
            std::cout << r->data << "  ";
            delete r;
            r = nullptr;
        }
    }
    
    bool isfullNode(Node* node) {
        // Node is full if it is either a leaf node or
        // it contains both left and right child
        if ((node->left == nullptr && node->right == nullptr) ||
            (node->left && node->right))
            return true;
        return false;
    }
    
private:
    Node* root;
};

int main(int argc, const char * argv[]) {
    Binarytree bt1;
    std::vector<std::optional<int>> dat1 {1,2,3,4,5,6,7};
    bt1.create(dat1);
    std::cout << "Tree1 complete_1: " << bt1.isComplete_1() << std::endl;
    std::cout << "Tree1 complete_2: " << bt1.isComplete_2() << std::endl;
    
    Binarytree bt2;
    std::vector<std::optional<int>> dat2 {1,2,3,4,5,std::nullopt,7};
    bt2.create(dat2);
    std::cout << "Tree2 complete_1: " << bt2.isComplete_1() << std::endl;
    std::cout << "Tree2 complete_2: " << bt2.isComplete_2() << std::endl;
    
    Binarytree bt3;
    std::vector<std::optional<int>> dat3 {2,3,4,5,std::nullopt,8, 10};
    bt3.create(dat3);
    std::cout << "Tree3 complete_1: " << bt3.isComplete_1() << std::endl;
    std::cout << "Tree3 complete_2: " << bt3.isComplete_2() << std::endl;
    return 0;
}
