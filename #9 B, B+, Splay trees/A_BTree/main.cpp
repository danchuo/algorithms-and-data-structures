#include <iostream>

class Node {
public:
    explicit Node(int);
    ~Node();

    Node **children;
    int size;
    int *keys;
    int degree;

    void splitHead();

    void splitNode(Node *previous);

    bool isLeaf();

    void pushKey(int);

    Node *getParent(Node *);

    size_t getSize() const;

    int64_t getSum();
};
Node::~Node() {
    delete[] keys;
    for (int i = 0; i < 2 * degree; ++i) {
        delete children[i];
    }
    delete[] children;
}
Node::Node(int degree) {
    this->degree = degree;
    size = 0;
    keys = new int[2 * degree - 1];
    children = new Node *[2 * degree];
    for (int i = 0; i < 2 * degree; ++i) {
        children[i] = nullptr;
    }
}
void Node::pushKey(int input_key) {
    if (size < 2 * degree - 1) {
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
                } else {
                    if (size - i - 1 == 0) {
                        keys[0] = input_key;
                    }
                }
            }
        } else {
            keys[0] = input_key;
        }

        ++size;
    }
}
void Node::splitHead() {
    Node *left_node = new Node(degree);
    Node *right_node = new Node(degree);

    for (int i = 0; i < degree - 1; ++i) {
        left_node->keys[i] = keys[i];
        ++(left_node->size);
    }

    for (int i = 0; i < degree; ++i) {
        (left_node->children)[i] = children[i];
    }

    for (int i = 0; i < degree - 1; ++i) {
        right_node->keys[i] = keys[i + degree];
        ++(right_node->size);
    }

    for (int i = 0; i < degree; ++i) {
        (right_node->children)[i] = children[i + degree];
    }

    keys[0] = keys[degree - 1];
    size = 1;

    for (int i = 2; i < 2 * degree; ++i) {
        children[i] = nullptr;
    }

    children[0] = left_node;
    children[1] = right_node;
}
bool Node::isLeaf() {
    return children[0] == nullptr;
}
size_t Node::getSize() const {
    size_t current_size = 0;

    for (int i = 0; i < 2 * degree; ++i) {
        if (children[i] != nullptr) {
            ++current_size;
            current_size += children[i]->getSize();
        }
    }
    return current_size;
}
int64_t Node::getSum() {
    int64_t current_sum = 0;

    if (isLeaf()) {
        for (int j = 0; j < size; ++j) {
            current_sum += keys[j];
        }
    } else {
        for (int i = 0; i < 2 * degree; ++i) {
            if (children[i] != nullptr) {
                current_sum += children[i]->getSum();
            }
        }
    }

    return current_sum;
}
void Node::splitNode(Node *previous) {
    Node *left_node = new Node(degree);
    Node *right_node = new Node(degree);

    for (int i = 0; i < degree - 1; ++i) {
        left_node->keys[i] = keys[i];
        ++(left_node->size);
    }

    for (int i = 0; i < degree; ++i) {
        (left_node->children)[i] = children[i];
    }

    for (int i = 0; i < degree - 1; ++i) {
        right_node->keys[i] = keys[i + degree];
        ++(right_node->size);
    }

    for (int i = 0; i < degree; ++i) {
        (right_node->children)[i] = children[i + degree];
    }

    previous->pushKey(keys[degree - 1]);

    int index_of_pointer = 0;
    for (int i = 0; i < 2 * degree; ++i) {
        if (previous->children[i] != nullptr && previous->children[i] == this) {
            index_of_pointer = i;
            break;
        }
    }

    previous->children[index_of_pointer] = left_node;

    Node *buffer = previous->children[index_of_pointer + 1];
    previous->children[index_of_pointer + 1] = right_node;

    for (int i = index_of_pointer + 2; i < 2 * degree; ++i) {
        if (previous->children[i] != nullptr) {
            Node *temp = previous->children[i];
            previous->children[i] = buffer;
            buffer = temp;
        } else {
            previous->children[i] = buffer;
            break;
        }
    }

    for (int i = 0; i < 2 * degree; ++i) {
        children[i] = nullptr;
    }
}
Node *Node::getParent(Node *head) {
    Node *current = head;
    Node *previous = nullptr;

    while (current != this) {
        int number_of_child = 0;

        while (number_of_child < current->size && current->keys[number_of_child] < keys[0]) {
            ++number_of_child;
        }

        previous = current;
        current = current->children[number_of_child];
    }

    return previous;
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
            int number_of_child = 0;

            while (number_of_child < current->size && current->keys[number_of_child] < input_key) {
                ++number_of_child;
            }

            current = current->children[number_of_child];
        } else {
            current->pushKey(input_key);
            Node *previous;
            while (current != nullptr && current->size == 2 * degree_ - 1 && current != head_) {
                previous = current->getParent(head_);
                current->splitNode(previous);
                delete current;
                current = previous;
            }

            current = nullptr;
        }
    }

    if (head_ == nullptr) {
        head_ = new Node(degree_);
        head_->pushKey(input_key);
    } else {
        if (head_->size == 2 * degree_ - 1) {
            head_->splitHead();
        }
    }
}
size_t BTree::size() const {
    return head_ == nullptr ? 0 : (head_->getSize() + 1);
}
int64_t BTree::sum() const {
    return head_ == nullptr ? 0 : head_->getSum();
}
