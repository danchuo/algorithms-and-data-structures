#include <iostream>

template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;
    ~Node();
    Node(KeyType, ValueType);
};

template <class KeyType, class ValueType>
Node<KeyType, ValueType>::Node(KeyType key, ValueType value) {
    key_ = key;
    value_ = value;
    next_ = nullptr;
}

template <class KeyType, class ValueType>
Node<KeyType, ValueType>::~Node() {
    delete next_;
}

template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable();
    explicit HashTable(Func);
    HashTable(size_t, double, Func = std::hash<KeyType>());

    ~HashTable();

    void insert(KeyType, ValueType);
    ValueType *find(KeyType);
    void erase(KeyType);

    Node<KeyType, ValueType> &operator[](uint64_t);
    Node<KeyType, ValueType> at(uint64_t);

    size_t size() const;
    size_t capacity() const;

private:
    void rehashing();

    Node<KeyType, ValueType> **nodes_;
    Func func_;
    size_t size_;
    size_t capacity_;
    double coefficient_;
};

template <class KeyType, class ValueType, class Func>
size_t HashTable<KeyType, ValueType, Func>::size() const {
    return size_;
}

template <class KeyType, class ValueType, class Func>
size_t HashTable<KeyType, ValueType, Func>::capacity() const {
    return capacity_;
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable() {
    size_ = 0;
    capacity_ = 100;
    coefficient_ = 0.5;
    nodes_ = new Node<KeyType, ValueType> *[capacity_];
    for (int i = 0; i < capacity_; ++i) {
        nodes_[i] = nullptr;
    }
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable(Func function) {
    func_ = function;
    size_ = 0;
    capacity_ = 100;
    coefficient_ = 0.5;
    nodes_ = new Node<KeyType, ValueType> *[capacity_];
    for (int i = 0; i < capacity_; ++i) {
        nodes_[i] = nullptr;
    }
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable(size_t capacity, double coefficient, Func function) {
    func_ = function;
    size_ = 0;
    capacity_ = capacity;
    coefficient_ = (coefficient > 0 && coefficient <= 1) ? coefficient : 0.5;
    nodes_ = new Node<KeyType, ValueType> *[capacity_];
    for (int i = 0; i < capacity_; ++i) {
        nodes_[i] = nullptr;
    }
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::~HashTable() {
    for (int i = 0; i < capacity_; ++i) {
        delete nodes_[i];
    }
    delete[] nodes_;
}

template <class KeyType, class ValueType, class Func>
ValueType *HashTable<KeyType, ValueType, Func>::find(KeyType key) {
    Node<KeyType, ValueType> *node = nodes_[func_(key)];
    return node != nullptr ? &(node->value_) : nullptr;
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::erase(KeyType key) {
    auto hash = func_(key);
    Node<KeyType, ValueType> *node = nodes_[hash];
    if (node != nullptr) {
        nodes_[hash] = nullptr;
        delete node;
        --size_;
    }
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::insert(KeyType key, ValueType value) {
    auto hash = func_(key);
    if (nodes_[hash] == nullptr) {
        nodes_[hash] = new Node<KeyType, ValueType>(key, value);
        ++size_;
    } else {
        Node<KeyType, ValueType> *current_node = nodes_[hash];
        while (current_node->next_ != nullptr) {
            if (current_node->key_ == key) {
                current_node->value_ = value;
                current_node = nullptr;
                break;
            }
            current_node = current_node->next_;
        }
        if (current_node != nullptr) {
            current_node->next_ = new Node<KeyType, ValueType>(key, value);
            ++size_;  // ??
        }
    }

    if (static_cast<double>(capacity_) / static_cast<double>(size_) > coefficient_) {
        rehashing();
    }
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::rehashing() {
    auto new_nodes = new Node<KeyType, ValueType> *[2 * capacity_];

    for (int i = 0; i < capacity_; ++i) {
        new_nodes[i + capacity_] = nullptr;
        new_nodes[i] = nodes_[i];
        nodes_[i] = nullptr;
    }

    capacity_ *= 2;
    delete[] nodes_;
    nodes_ = new_nodes;
}

template <class KeyType, class ValueType, class Func>
Node<KeyType, ValueType> &HashTable<KeyType, ValueType, Func>::operator[](uint64_t hash) {
    if (hash > capacity_) {
        throw std::out_of_range("error");
    }

    Node<KeyType, ValueType> *node = nodes_[hash];

    if (node == nullptr) {
        throw std::runtime_error("error");
    }

    return *node;
}

template <class KeyType, class ValueType, class Func>
Node<KeyType, ValueType> HashTable<KeyType, ValueType, Func>::at(uint64_t hash) {
    return operator[](hash);
}
