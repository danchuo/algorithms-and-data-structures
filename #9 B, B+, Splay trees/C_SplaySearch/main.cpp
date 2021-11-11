#include <iostream>
struct Node {
public:
    int key;
    Node *left;
    Node *right;
    ~Node();
};
Node::~Node() {
    delete left;
    delete right;
}

class SplayTree {
public:
    SplayTree();

    ~SplayTree();

    void insert(int input_key);

    Node *find(int) const;

    int splay(Node *);

    int getHeight() const;

private:
    Node *head_;

    void countHeight(Node *current, int current_height, int *max) const;
};
SplayTree::SplayTree() {
    head_ = nullptr;
}
SplayTree::~SplayTree() {
    delete head_;
}
int SplayTree::getHeight() const {
    if (head_ != nullptr) {
        int max = 0;
        countHeight(head_, 0, &max);
        return max;
    } else {
        return 0;
    }
}
void SplayTree::countHeight(Node *current, int current_height, int *max) const {
    if (current->left != nullptr) {
        countHeight(current->left, current_height + 1, max);
    } else {
        if (current_height > (*max)) {
            (*max) = current_height;
        }
    }

    if (current->right != nullptr) {
        countHeight(current->right, current_height + 1, max);
    } else {
        if (current_height > (*max)) {
            (*max) = current_height;
        }
    }
}
void SplayTree::insert(int input_key) {
    Node *current = head_;

    while (current != nullptr) {
        if (input_key < current->key) {
            if (current->left != nullptr) {
                current = current->left;
            } else {
                current->left = new Node{input_key};
                current = nullptr;
            }
        } else {
            if (input_key > current->key) {
                if (current->right != nullptr) {
                    current = current->right;
                } else {
                    current->right = new Node{input_key};
                    current = nullptr;
                }
            }
        }
    }

    if (head_ == nullptr) {
        head_ = new Node{input_key};
    }
}
Node *SplayTree::find(int input_key) const {
    Node *current = head_;

    while (current != nullptr) {
        if (current->key == input_key) {
            return current;
        } else {
            if (input_key < current->key) {
                if (current->left != nullptr) {
                    current = current->left;
                } else {
                    current = nullptr;
                }
            } else {
                if (input_key > current->key) {
                    if (current->right != nullptr) {
                        current = current->right;
                    } else {
                        current->right = new Node{input_key};
                        current = nullptr;
                    }
                }
            }
        }
    }

    return current;
}
int SplayTree::splay(Node *) {
    return 1;
}
