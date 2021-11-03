#include <iostream>
#include <string>

class TreeInt {
public:
    int data;
    TreeInt *left;
    TreeInt *right;
    explicit TreeInt(int data);
    ~TreeInt();

    std::string isBalanced();

    void push(int input_data);

    static TreeInt *createTreeFromInput();

    static int getHeight(TreeInt *tree_int, int *height);
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
std::string TreeInt::isBalanced() {
    int height;
    try {
        getHeight(this, &height);
    } catch (...) {
        return "NO";
    }

    if (abs(height) > 1) {
        return "NO";
    }

    return "YES";
}
int TreeInt::getHeight(TreeInt *tree_int, int *height) {
    if (tree_int == nullptr) {
        return 0;
    }
    int left_tree = getHeight(tree_int->left, height);
    int right_tree = getHeight(tree_int->right, height);

    *height = left_tree - right_tree;

    if (abs(*height) > 1) {
        throw "NO";
    }

    return (left_tree > right_tree ? left_tree : right_tree) + 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TreeInt *tree_int = TreeInt::createTreeFromInput();

    if (tree_int == nullptr) {
        std::cout << "YES";
    } else {
        std::cout << tree_int->isBalanced();
    }
    delete tree_int;
    return 0;
}
