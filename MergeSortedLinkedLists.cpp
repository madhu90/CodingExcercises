//
// Given two sorted linked lists, we need to efficiently merge them into a single list:
// input1: {1,3,5}
// input2: {2,4,6,7}
// output: {1,2,3,4,5,6,7}
// There are a couple of ways to do this:
// We can create a brand new list and this will have a time and space complexity of O(n)
// If a new list is not needed, we can reduce the space ocmplexity to O(1). This is not possible
// with arrays because we can't modify links. With lists, we can just keep updating the "next"
// pointer to an appropriate value
//

#include <iostream>
#include <vector>

class Node {
public:
    int data;
    Node* next;
};

class LinkedList {
public:
    LinkedList() {
        
    }
    
    LinkedList(Node* list)
    : root(list) {
        
    }
    
    LinkedList(const std::vector<int>& vec)
    : root(nullptr) {
        root = new Node({vec[0], nullptr});
        Node* prev = root;
        
        for (size_t i = 1; i < vec.size(); ++i) {
            Node* newNode = new Node({vec[i], nullptr});
            prev->next = newNode;
            prev = newNode;
        }
        
        prev->next = nullptr;
    }
    
    ~LinkedList() {
        std::cout << "Destroying: ";
        cleanup(root);
        std::cout << std::endl;
    }
    
    Node* getRoot() const {
        return root;
    }
    
    Node*& getModifyableroot() {
        return root;
    }
    
    void setRoot(Node* value) {
        root = value;
    }
    
    void print() {
        std::cout << "List : ";
        Node* temp = root;
        
        while (temp != nullptr) {
            std::cout << temp->data << "  ";
            temp = temp->next;
        }
        
        std::cout << std::endl;
    }
    
    // Time complexity is O(n)
    // Space complexity is also O(n)
    LinkedList merge1(const LinkedList& other) {
        Node* newroot = nullptr;
        Node* newtail = nullptr;
        Node* temp = nullptr;
        Node* left = root;
        Node* right = other.getRoot();
        
        if (left->data < right->data) {
            newroot = new Node({left->data, nullptr});
            left = left->next;
        } else {
            newroot = new Node({right->data, nullptr});
            right = right->next;
        }
        
        newtail = newroot;
        
        while (left && right) {
            if (left->data < right->data) {
                temp = new Node({left->data, nullptr});
                left = left->next;
            } else {
                temp = new Node({right->data, nullptr});
                right = right->next;
            }
            newtail->next = temp;
            newtail = temp; // this is imp to make sure the list is connected
        }
        
        while (left) {
            temp = new Node({left->data, nullptr});
            left = left->next;
            newtail->next = temp;
            newtail = temp;
        }
        
        while (right) {
            temp = new Node({right->data, nullptr});
            right = right->next;
            newtail->next = temp;
            newtail = temp;
        }
        
        return LinkedList(newroot);
    }
    
    LinkedList merge2(LinkedList& other) {
        // We empty the list in other and merge it
        // with this
        Node* left = root;
        Node* right = other.getModifyableroot();
        LinkedList newlist = LinkedList(SortedMerge(left, right));
        setRoot(nullptr);
        other.setRoot(nullptr);
        return newlist;
    }
    
private:
    
    Node* SortedMerge(Node* left, Node* right) {
        if (left == nullptr)
            return right;
        
        if (right == nullptr)
            return left;
        
        Node* temp = nullptr;
        
        if (left->data < right->data) {
            temp = left;
            temp->next  = SortedMerge(left->next, right);
        } else {
            temp = right;
            temp->next = SortedMerge(left, right->next);
        }
        
        return temp;
    }
    
    void cleanup(Node*& node) {
        if (node) {
            cleanup(node->next);
            std::cout << node->data << "  ";
            delete node;
            node = nullptr;
        }
    }
    
private:
    Node* root;
};

int main(int argc, const char * argv[]) {
    // O(n) space and time complexity
    LinkedList obj1({1,3,5});
    LinkedList obj2({2,4,6,7});
    obj1.print();
    obj2.print();
    LinkedList obj3 = obj1.merge1(obj2);
    obj3.print();
    
    // O(n) time and O(1) space complexity
    LinkedList obj4({1,3,5});
    LinkedList obj5({2,4,6,7});
    obj4.print();
    obj5.print();
    LinkedList obj6 = obj4.merge2(obj5);
    obj6.print();
    return 0;
}
