#include <iostream>

class DSUList;
class Node {
public:
    explicit Node(DSUList *owner, int value) {
        owner_ = owner;
        this->value_ = value;
        right_ = nullptr;
    }

    ~Node() {
        delete right_;
    }

    DSUList *owner_;
    int value_;
    Node *right_;
};

class DSUList {
public:
    explicit DSUList(int key) {
        head_ = new Node(this, key);
        tail_ = head_;
    }

    Node *findLeft() {
        return tail_;
    }

    void connectWith(DSUList *other) {
        DSUList *current = this;

        Node *current_node = other->tail_;
        while (current_node != nullptr) {
            current_node->owner_ = current;
            current_node = current_node->right_;
        }

        (current->head_)->right_ = other->tail_;
        current->head_ = other->head_;

        delete other;
    }

    Node *head_;

private:
    Node *tail_;
};

void connectWith(Node *left_node, Node *right_node) {
    left_node->owner_->connectWith(right_node->owner_);
}

void printList(Node *left_node) {
    while (left_node != nullptr) {
        std::cout << (left_node->value_ + 1) << ' ';
        left_node = left_node->right_;
    }
}

void findOriginalLocation(int number_of_kittens) {
    DSUList **kittens = new DSUList *[number_of_kittens];
    Node **kitten_nodes = new Node *[number_of_kittens];
    for (int i = 0; i < number_of_kittens; ++i) {
        kittens[i] = new DSUList(i);
    }

    for (int i = 0; i < number_of_kittens; ++i) {
        kitten_nodes[i] = kittens[i]->head_;
    }

    int left;
    int right;

    for (int i = 0; i < number_of_kittens - 1; ++i) {
        std::cin >> left >> right;
        left -= 1;
        right -= 1;
        connectWith(kitten_nodes[left], kitten_nodes[right]);
    }

    Node *left_node = kitten_nodes[0]->owner_->findLeft();

    printList(left_node);

    delete left_node->owner_;

    delete[] kittens;
    delete left_node;
    delete[] kitten_nodes;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_kittens;
    std::cin >> number_of_kittens;

    findOriginalLocation(number_of_kittens);

    return 0;
}
