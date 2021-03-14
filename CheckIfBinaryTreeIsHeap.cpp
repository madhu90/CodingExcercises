//
// Check if the given binary tree is a heap
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
    
    bool isMinHeap() {
        return isMinHeapHelper(root, 0, size(root));
    }
    

    ~Binarytree() {
        std::cout << "Destroying:  ";
        cleanup(root);
        std::cout << std::endl;
    }
    
private:
    bool isMinHeapHelper(Node* node, int indx, int sz) {
        if (node == nullptr)
            return true;
        
        // For min-heap, parent must be smaller than the children
        // And it should be a complete binary tree
        if (!doesNodeSatisfyStructureProperty(2*indx+1, sz) || /*Check if left child is within bounds*/
            !doesNodeSatisfyStructureProperty(2*indx+2, sz) || /*Check if right child is within bounds*/
            !doesNodeSatisfyOrderProperty(node)) /*Check parent is smaller than left and right children*/
            return false;
        
        return isMinHeapHelper(node->left, 2*indx+1, sz) || isMinHeapHelper(node->right, 2*indx+2, sz);
    }
    
    int size(Node* root) {
        if (root == nullptr)
            return 0;
        
        return 1 + size(root->left) + size(root->right);
    }
    
    bool doesNodeSatisfyOrderProperty(Node* node) {
        if ((node->left && (node->data >= node->left->data)) || (node->right && (node->data >= node->right->data))) {
            return false;
        }
        return true;
    }
    
    bool doesNodeSatisfyStructureProperty(int indx, int sz) {
        return indx < sz;
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
    
private:
    Node* root;
};


int main(int argc, const char * argv[]) {
    Binarytree bt1;
    std::vector<std::optional<int>> dat1 {2,3,4,5,6,8,10};
    bt1.create(dat1);
    std::cout << "Tree 1 is min heap: " << bt1.isMinHeap() << std::endl;
    
    Binarytree bt2;
    std::vector<std::optional<int>> dat2 {2,3,4,5,std::nullopt,8, 10};
    bt2.create(dat2);
    std::cout << "Tree 2 is min heap: " << bt2.isMinHeap() << std::endl;
    
    Binarytree bt3;
    std::vector<std::optional<int>> dat3 {5,3,8,2,4,6,10};
    bt3.create(dat3);
    std::cout << "Tree 3 is min heap: " << bt3.isMinHeap() << std::endl;
    return 0;
}
