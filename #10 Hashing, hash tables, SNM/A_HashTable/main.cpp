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
    void rehash();
    void insertAgain(Node<KeyType, ValueType> *);
    void deleteNode(Node<KeyType, ValueType> *);

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
        deleteNode(nodes_[i]);
    }
    delete[] nodes_;
}

template <class KeyType, class ValueType, class Func>
ValueType *HashTable<KeyType, ValueType, Func>::find(KeyType key) {
    Node<KeyType, ValueType> *node = nodes_[func_(key) % capacity_];
    if (node != nullptr) {
        while (node != nullptr) {
            if (node->key_ == key) {
                return &(node->value_);
            }
            node = node->next_;
        }
    }
    return nullptr;
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::erase(KeyType key) {
    auto hash = func_(key) % capacity_;
    Node<KeyType, ValueType> *previous_node = nullptr;
    Node<KeyType, ValueType> *current_node = nodes_[hash];
    if (current_node != nullptr) {
        while (current_node != nullptr) {
            if (current_node->key_ == key) {
                if (previous_node != nullptr) {
                    previous_node->next_ = current_node->next_;
                } else {
                    nodes_[hash] = current_node->next_;
                }

                current_node->next_ = nullptr;
                deleteNode(current_node);
                return;
            }
            previous_node = current_node;
            current_node = current_node->next_;
        }
    }
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::insert(KeyType key, ValueType value) {
    auto hash = func_(key) % capacity_;
    if (nodes_[hash] == nullptr) {
        nodes_[hash] = new Node<KeyType, ValueType>(key, value);
        ++size_;
    } else {
        Node<KeyType, ValueType> *previous_node = nodes_[hash];
        Node<KeyType, ValueType> *current_node = previous_node->next_;

        if (previous_node->key_ == key) {
            previous_node->value_ = value;
            return;
        }

        while (current_node != nullptr) {
            if (current_node->key_ == key) {
                current_node->value_ = value;
                return;
            }
            previous_node = current_node;
            current_node = current_node->next_;
        }

        if (previous_node != nullptr) {
            previous_node->next_ = new Node<KeyType, ValueType>(key, value);
            ++size_;
        }
    }

    if (static_cast<double>(size_) / static_cast<double>(capacity_) > coefficient_) {
        rehash();
    }
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::rehash() {
    capacity_ *= 2;
    Node<KeyType, ValueType> **old_nodes = nodes_;
    nodes_ = new Node<KeyType, ValueType> *[capacity_];

    for (int i = 0; i < capacity_; ++i) {
        nodes_[i] = nullptr;
    }

    for (int i = 0; i < capacity_ / 2; ++i) {
        Node<KeyType, ValueType> *current_node = old_nodes[i];
        if (current_node != nullptr) {
            insertAgain(current_node);
            old_nodes[i] = nullptr;
        }
    }

    delete[] old_nodes;
}

template <class KeyType, class ValueType, class Func>
Node<KeyType, ValueType> &HashTable<KeyType, ValueType, Func>::operator[](uint64_t hash) {
    if (hash >= capacity_) {
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

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::insertAgain(Node<KeyType, ValueType> *input_node) {
    auto hash = func_(input_node->key_) % capacity_;
    Node<KeyType, ValueType> *next_node = input_node->next_;
    input_node->next_ = nullptr;

    if (nodes_[hash] == nullptr) {
        nodes_[hash] = input_node;
    } else {
        Node<KeyType, ValueType> *current_node = nodes_[hash];
        while (current_node->next_ != nullptr) {
            current_node = current_node->next_;
        }

        current_node->next_ = input_node;
    }

    if (next_node != nullptr) {
        insertAgain(next_node);
    }
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::deleteNode(Node<KeyType, ValueType> *node_to_delete) {
    while (node_to_delete != nullptr) {
        Node<KeyType, ValueType> *previous_node = node_to_delete;
        node_to_delete = node_to_delete->next_;
        delete previous_node;
        --size_;
    }
}
