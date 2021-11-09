#include <iostream>

class TreeInt {
public:
    static const int kDefaultKey = 1000000001;
    int key;
    int number;
    TreeInt *left;
    TreeInt *right;
    bool is_red;
    TreeInt();
    ~TreeInt();

    void countHeight(int current_height, int *max);

    static bool isRBTreeCorrect(int tree_size);

private:
    static TreeInt *parseNode();
    bool tryAddNode(TreeInt *node, bool is_parent_red);
    bool isBalanced();
    int getHeight(TreeInt *tree_int, int *height);
};

TreeInt::TreeInt() {
    this->number = 0;
    this->key = kDefaultKey;
    left = nullptr;
    right = nullptr;
    is_red = false;
}

TreeInt::~TreeInt() {
    delete right;
    delete left;
}

bool TreeInt::isRBTreeCorrect(int tree_size) {
    TreeInt *tree_int = new TreeInt();
    std::cin >> tree_int->number;
    bool is_rb_tree_correct = true;
    TreeInt *current_node;

    for (int i = 0; i < tree_size; ++i) {
        if (is_rb_tree_correct) {
            current_node = parseNode();
            is_rb_tree_correct = tree_int->tryAddNode(current_node, true);
            delete current_node;
        } else {
            break;
        }
    }

    if (is_rb_tree_correct) {
        is_rb_tree_correct = tree_int->isBalanced();
    }

    delete tree_int;
    return is_rb_tree_correct;
}
TreeInt *TreeInt::parseNode() {
    TreeInt *node = new TreeInt();
    std::cin >> node->number;
    std::cin >> node->key;

    int left_right_number;

    std::cin >> left_right_number;

    if (left_right_number != 0) {
        node->left = new TreeInt();
        node->left->number = left_right_number;
    } else {
        std::cin.clear();
        std::cin.ignore(5, '\n');
    }

    std::cin >> left_right_number;

    if (left_right_number != 0) {
        node->right = new TreeInt();
        node->right->number = left_right_number;
    } else {
        std::cin.clear();
        std::cin.ignore(5, '\n');
    }

    char color;
    std::cin >> color;
    node->is_red = (color == 'R');

    return node;
}
bool TreeInt::tryAddNode(TreeInt *node, bool is_parent_red) {
    if (node->number == number) {
        if (is_parent_red && node->is_red) {
            return false;
        }
        key = node->key;
        left = node->left;
        right = node->right;
        is_red = node->is_red;
        node->left = nullptr;
        node->right = nullptr;
        return true;
    }

    if (key != kDefaultKey) {
        if (node->key < key) {
            if (left != nullptr) {
                return left->tryAddNode(node, is_red);
            }
        } else {
            if (node->key > key) {
                if (right != nullptr) {
                    return right->tryAddNode(node, is_red);
                }
            }
        }
    }

    return false;
}

bool TreeInt::isBalanced() {
    int height;
    try {
        getHeight(this, &height);
    } catch (...) {
        return false;
    }

    if (abs(height) > 0) {
        return false;
    }

    return true;
}
int TreeInt::getHeight(TreeInt *tree_int, int *height) {
    if (tree_int == nullptr) {
        return 0;
    }
    int left_tree = getHeight(tree_int->left, height);
    int right_tree = getHeight(tree_int->right, height);

    *height = left_tree - right_tree;

    if (abs(*height) > 0) {
        throw "NO";
    }

    return (left_tree > right_tree ? left_tree : right_tree) + (is_red ? 0 : 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tree_size;
    std::cin >> tree_size;
    if (tree_size == 0) {
        std::cout << "YES";
    } else {
        std::cout << (TreeInt::isRBTreeCorrect(tree_size) ? "YES" : "NO");
    }
    return 0;
}
