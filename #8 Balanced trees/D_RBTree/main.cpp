#include <iostream>

template<class ValueType>
class RBTree {
public:
    RBTree();

    RBTree(const RBTree &other);

    RBTree &operator=(const RBTree &other);

    ~RBTree();

    size_t size() const;

    bool empty() const;

    void insert(const ValueType &value);

    void erase(const ValueType &value);

    ValueType *lower_bound(const ValueType &value) const;  // NOLINT

    ValueType *find(const ValueType &value) const;

    ValueType *traversal() const;
private:
    ValueType key_;
    RBTree *left_;
    RBTree *right_;
    bool is_red_;

    size_t getSizeRecursive(const RBTree &tree);

    void insertRecursive(const RBTree &tree, const ValueType &value);
};
template<class ValueType>
RBTree<ValueType>::RBTree() {
    left_ = nullptr;
    right_ = nullptr;
    is_red_ = false;
    key_ = nullptr;
}
template<class ValueType>
RBTree<ValueType>::~RBTree() {
    delete left_;
    delete right_;
    delete key_;
}
template<class ValueType>

size_t RBTree<ValueType>::size() const {
    return getSizeRecursive(this);
}
template<class ValueType>
size_t RBTree<ValueType>::getSizeRecursive(const RBTree &tree) {
    if (tree == nullptr) {
        return 0;
    }
    return getSizeRecursive(tree.left_) + getSizeRecursive(tree.right_) + 1;
}
template<class ValueType>
bool RBTree<ValueType>::empty() const {
    return this->key_ == nullptr;
}
template<class ValueType>
void RBTree<ValueType>::insert(const ValueType &value) {
    insertRecursive(this, value);
}
template<class ValueType>
void RBTree<ValueType>::insertRecursive(const RBTree &tree, const ValueType &value) {

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
