#include <string>
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

    ~HashTable();

    void insert(KeyType, ValueType);
    bool hasKey(KeyType);

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
HashTable<KeyType, ValueType, Func>::HashTable() {
    size_ = 0;
    capacity_ = 10000;
    coefficient_ = 0.5;
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
template <class KeyType, class ValueType, class Func>
bool HashTable<KeyType, ValueType, Func>::hasKey(KeyType key) {
    Node<KeyType, ValueType> *node = nodes_[func_(key) % capacity_];
    if (node != nullptr) {
        while (node != nullptr) {
            if (node->key_ == key) {
                return true;
            }
            node = node->next_;
        }
    }
    return false;
}

class BloomFilter {
public:
    BloomFilter(size_t hashes, size_t number_of_bits);

    ~BloomFilter();

    void add(const std::string &obj);

    bool verify(const std::string &obj);

    double getFPRate() const;

    size_t numberOfHashFunctions() const;
    size_t numberOfBits() const;

private:
    size_t hashes_;
    size_t number_of_bits_;
    int *bits_;
    size_t number_of_requests_;
    size_t number_of_false_positive_answers_;
    HashTable<std::string, char> *hash_table_;
    static char const *k_salt;
    size_t getNHash(const std::string &string_to_hash, int);
};
const char *BloomFilter::k_salt = "sL0NiK?";

BloomFilter::BloomFilter(size_t hashes, size_t number_of_bits) {
    this->hashes_ = hashes;
    this->number_of_bits_ = number_of_bits;
    this->number_of_requests_ = 0;
    this->number_of_false_positive_answers_ = 0;
    hash_table_ = new HashTable<std::string, char>();
    this->bits_ = new int[number_of_bits_];
    for (size_t i = 0; i < number_of_bits_; ++i) {
        bits_[i] = 0;
    }
}
size_t BloomFilter::numberOfBits() const {
    return number_of_bits_;
}
size_t BloomFilter::numberOfHashFunctions() const {
    return hashes_;
}
BloomFilter::~BloomFilter() {
    delete[] bits_;
    delete hash_table_;
}
double BloomFilter::getFPRate() const {
    double result;

    if (number_of_requests_ == 0) {
        result = 0;
    } else {
        result = number_of_false_positive_answers_ / number_of_requests_;
    }

    return result;
}
bool BloomFilter::verify(const std::string &obj) {
    bool result = true;

    for (size_t i = 0; i < hashes_; ++i) {
        if (bits_[getNHash(obj, i)] == 0) {
            result = false;
            break;
        }
    }

    if (result && !hash_table_->hasKey(obj + k_salt)) {
        ++number_of_false_positive_answers_;
    }

    ++number_of_requests_;
    return result;
}
void BloomFilter::add(const std::string &obj) {
    for (size_t i = 0; i < hashes_; ++i) {
        bits_[getNHash(obj, i)] = 1;
    }

    hash_table_->insert(obj + k_salt, 0);
}
size_t BloomFilter::getNHash(const std::string &string_to_hash, int number) {
    size_t result;

    if (number == 0) {
        result = std::hash<std::string>{}(string_to_hash);
    } else {
        result = std::hash<std::string>{}(string_to_hash + std::to_string(number));
    }
    return result % number_of_bits_;
}
