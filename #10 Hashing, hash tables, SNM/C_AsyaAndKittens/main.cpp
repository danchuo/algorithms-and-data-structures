#include <iostream>

class Node {
public:
    explicit Node(int key) {
        this->key_ = key;
        left_ = nullptr;
        right_ = nullptr;
    }

    ~Node() {
        delete right_;
    }

    void printList() {
        Node *left_node = this;
        while (left_node != nullptr) {
            std::cout << (left_node->key_ + 1) << ' ';
            left_node = left_node->right_;
        }
    }

    Node *findLeft() {
        Node *left_node = this;
        while (left_node->left_ != nullptr) {
            left_node = left_node->left_;
        }
        return left_node;
    }

    void connectWith(Node *other) {
        Node *left_node = this;
        Node *right_node = other;

        while (left_node->right_ != nullptr) {
            left_node = left_node->right_;
        }

        while (right_node->left_ != nullptr) {
            right_node = right_node->left_;
        }

        left_node->right_ = right_node;
        right_node->left_ = left_node;
    }

private:
    int key_;
    Node *left_;
    Node *right_;
};

void findOriginalLocation(int number_of_kittens) {
    Node **kittens = new Node *[number_of_kittens];
    for (int i = 0; i < number_of_kittens; ++i) {
        kittens[i] = new Node(i);
    }

    int left;
    int right;

    for (int i = 0; i < number_of_kittens - 1; ++i) {
        std::cin >> left >> right;
        left -= 1;
        right -= 1;
        kittens[left]->connectWith(kittens[right]);
    }

    Node *left_node = kittens[rand() % number_of_kittens]->findLeft();

    left_node->printList();

    for (int i = 0; i < number_of_kittens; ++i) {
        kittens[i] = nullptr;
    }

    delete[] kittens;
    delete left_node;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_kittens;
    std::cin >> number_of_kittens;

    findOriginalLocation(number_of_kittens);

    return 0;
}
