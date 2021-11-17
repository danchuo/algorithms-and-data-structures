#include <iostream>

class Node {
public:
    int *keys;
    Node **children;
    int size;
    Node(int);
    ~Node();

    bool isLeaf();

    int getMaxKey();
    int getMinKey();
    void pushKey(int input_key, int max_keys_number);
    void splitNode(int);
};
Node::~Node() {
    delete[] keys;
    if (children != nullptr) {
        delete[] (*children);
    }
    delete children;
}
Node::Node(int degree) {
    size = 0;
    keys = new int[2 * degree - 1];
    children = new Node *[2 * degree];
    for (int i = 0; i < 2 * degree; ++i) {
        children[i] = nullptr;
    }
}
int Node::getMaxKey() {
    return keys[size - 1];
}
int Node::getMinKey() {
    return keys[0];
}
void Node::pushKey(int input_key, int max_keys_number) {
    if (size < max_keys_number) {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == input_key) {
                return;
            }
        }
        if (size > 0) {
            for (int i = 0; i < size; ++i) {
                keys[size - i] = keys[size - i - 1];
                if (keys[size - i - 1] < input_key) {
                    keys[size - i] = input_key;
                    break;
                }
            }
        } else {
            keys[0] = input_key;
        }

        ++size;
    }
}
void Node::splitNode(int degree) {
    Node *y1 = new Node(2 * degree - 1);
    Node *y2 = new Node(2 * degree - 1);

    for (int i = 0; i < degree - 1; ++i) {
        y1->keys[i] = keys[i];
        ++(y1->size);
    }

    for (int i = 0; i < degree; ++i) {
        (y1->children)[i] = children[i];
    }

    for (int i = 0; i < degree - 1; ++i) {
        y2->keys[i] = keys[i + degree];
        ++(y2->size);
    }

    for (int i = 0; i < degree; ++i) {
        (y2->children)[i] = children[i + degree];
    }

    keys[0] = keys[degree - 1];
    size = 1;

    for (int i = 0; i < 2 * degree; ++i) {
        children[i] = nullptr;
    }

    children[0] = y1;
    children[1] = y2;
}
bool Node::isLeaf() {
    return children[0] == nullptr;
}

class BTree {
public:
    explicit BTree(int);

    ~BTree();

    void insert(int);

    size_t size() const;

    int64_t sum() const;

private:
    int degree_;
    Node *head_;
};
BTree::BTree(int degree) {
    this->degree_ = degree;
    head_ = nullptr;
}
BTree::~BTree() {
    delete head_;
}

void BTree::insert(int input_key) {
    Node *current = head_;

    while (current != nullptr) {
        if (!current->isLeaf()) {
            int numberOfChild = 0;

            while (numberOfChild < 2 * degree_ && current->keys[numberOfChild] < input_key) {
                ++numberOfChild;
            }

            current = current->children[numberOfChild];
        } else {
            current->pushKey(input_key, 2 * degree_ - 1);
            if (current->size == 2 * degree_ - 1) {
                current->splitNode(degree_);
            }
            current = nullptr;
        }
    }

    if (head_ == nullptr) {
        head_ = new Node(degree_);
        head_->pushKey(input_key, 2 * degree_ - 1);
    } else {
        if (head_->size == 2 * degree_ - 1) {
            head_->splitNode(degree_);
        }
    }
}

int main() {
    BTree *tree = new BTree(2);
    tree->insert(1);
    tree->insert(2);
    tree->insert(3);
    tree->insert(4);

    delete tree;
    return 0;
}

