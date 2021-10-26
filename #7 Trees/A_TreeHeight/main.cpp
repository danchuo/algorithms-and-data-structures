#include <iostream>

class TreeInt {
public:
    int data;
    TreeInt *left;
    TreeInt *right;
    explicit TreeInt(int data);
    ~TreeInt();

    void push(int input_data);
    void getHeight(int current_height, int *max);

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
void TreeInt::getHeight(int current_height, int *max) {
    if (left != nullptr) {
        return left->getHeight(current_height + 1, max);
    } else {
        if (current_height > (*max)) {
            (*max) = current_height;
        }
    }

    if (right != nullptr) {
        return right->getHeight(current_height + 1, max);
    } else {
        if (current_height > (*max)) {
            (*max) = current_height;
        }
    }
}

TreeInt *TreeInt::createTreeFromInput() {
    TreeInt *tree_int = nullptr;
    int input_data;
    std::cin >> input_data;

    while (input_data != 0) {
        if (tree_int == nullptr) {
            tree_int = new TreeInt(input_data);
        } else {
            tree_int->push(input_data);
        }
        std::cin >> input_data;
    }

    return tree_int;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TreeInt *tree_int = TreeInt::createTreeFromInput();

    int max = 0;
    if (tree_int != nullptr) {
        tree_int->getHeight(1, &max);
        std::cout << max;
    } else {
        std::cout << 0;
    }

    delete tree_int;

    return 0;
}
