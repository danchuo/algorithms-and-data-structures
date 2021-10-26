#include <iostream>

class TreeInt {
public:
    int data;
    TreeInt *left;
    TreeInt *right;
    explicit TreeInt(int data);
    ~TreeInt();

    void push(int input_data);

    void postOrder(TreeInt *root);

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

void TreeInt::postOrder(TreeInt *root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        if (root->left == nullptr && root->right == nullptr) {
            std::cout << root->data << '\n';
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TreeInt *tree_int = TreeInt::createTreeFromInput();

    if (tree_int != nullptr) {
        tree_int->postOrder(tree_int);
    }

    delete tree_int;
    return 0;
}
