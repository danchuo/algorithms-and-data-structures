#include <iostream>

class TreeInt {
public:
    int data;
    TreeInt *left;
    TreeInt *right;
    explicit TreeInt(int data);
    ~TreeInt();

    void push(int input_data);
    void countHeight(int current_height, int *max);

    static int getHeight(TreeInt *tree_int);

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
void TreeInt::countHeight(int current_height, int *max) {
    if (left != nullptr) {
        left->countHeight(current_height + 1, max);
    } else {
        if (current_height > (*max)) {
            (*max) = current_height;
        }
    }

    if (right != nullptr) {
        right->countHeight(current_height + 1, max);
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

int TreeInt::getHeight(TreeInt *tree_int) {
    if (tree_int != nullptr) {
        int max = 0;
        tree_int->countHeight(1, &max);
        return max;
    } else {
        return 0;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TreeInt *tree_int = TreeInt::createTreeFromInput();

    std::cout << TreeInt::getHeight(tree_int);

    delete tree_int;

    return 0;
}
