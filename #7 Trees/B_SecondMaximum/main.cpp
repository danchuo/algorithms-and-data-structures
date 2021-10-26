#include <iostream>

class TreeInt {
public:
    int data;
    TreeInt *left;
    TreeInt *right;
    explicit TreeInt(int data);
    ~TreeInt();

    void push(int input_data);

    int findMax();

    int getSecondMaximum();

    static TreeInt *createTreeFromInput();
};

TreeInt::TreeInt(int data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
}

TreeInt::~TreeInt() {
    delete right;
    delete left;
}

void TreeInt::push(int input_data) {
    if (input_data < data) {
        if (left != nullptr) {
            left->push(input_data);
        } else {
            left = new TreeInt(input_data);
        }
    } else {
        if (input_data > data) {
            if (right != nullptr) {
                right->push(input_data);
            } else {
                right = new TreeInt(input_data);
            }
        }
    }
}

TreeInt *TreeInt::createTreeFromInput() {
    int input_data;
    std::cin >> input_data;
    TreeInt *tree_int = new TreeInt(input_data);

    std::cin >> input_data;
    while (input_data != 0) {
        tree_int->push(input_data);
        std::cin >> input_data;
    }

    return tree_int;
}

int TreeInt::getSecondMaximum() {
    TreeInt *current = this;

    while (current->right != nullptr) {
        if (current->right->right == nullptr && current->right->left == nullptr) {
            return current->data;
        }
        current = current->right;
    }

    return current->left->findMax();
}

int TreeInt::findMax() {
    TreeInt *current = this;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->data;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TreeInt *tree_int = TreeInt::createTreeFromInput();

    std::cout << tree_int->getSecondMaximum();

    delete tree_int;

    return 0;
}
