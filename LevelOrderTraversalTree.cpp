//
// Level order traversal of a binary tree. This is an iterative implementation.
// We go through the nodes in each level of the tree and we use a queue for this
//

#include <iostream>
#include <vector>
#include <optional>
#include <queue>

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
    
    void levelOrder() {
        std::queue<Node*> queue;
        queue.push(root);
        std::cout << "Level order traversal" << std::endl;
        while (!queue.empty()) {
            Node* curr = queue.front();
            queue.pop();
            std::cout << curr->data << "  ";
            if (curr->left)
                queue.push(curr->left);
            if(curr->right)
                queue.push(curr->right);
        }
        
        std::cout << std::endl;
    }
    
    ~Binarytree() {
        std::cout << "Destroying:  ";
        cleanup(root);
        std::cout << std::endl;
    }
    
private:
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
    std::vector<std::optional<int>> dat1 {1,2,3,4,5,std::nullopt, 7};
    bt1.create(dat1);
    bt1.levelOrder();
    
    Binarytree bt2;
    std::vector<std::optional<int>> dat2 {1,2,3,4,5,6,7};
    bt2.create(dat2);
    bt2.levelOrder();
    return 0;
}
