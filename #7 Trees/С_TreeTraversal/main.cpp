#include <iostream>

class TreeInt {
public:
    int data;
    TreeInt *left;
    TreeInt *right;
    explicit TreeInt(int data);
    ~TreeInt();

    void push(int input_data);

    void inOrder(TreeInt *root);

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

void TreeInt::inOrder(TreeInt *root) {
    if (root) {
        inOrder(root->left);
        std::cout << root->data << '\n';
        inOrder(root->right);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TreeInt *tree_int = TreeInt::createTreeFromInput();

    if (tree_int != nullptr) {
        tree_int->inOrder(tree_int);
    }

    delete tree_int;

    return 0;
}
