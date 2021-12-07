#include <string>

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

    size_t getNHash(const std::string &string_to_hash, int);
};
BloomFilter::BloomFilter(size_t hashes, size_t number_of_bits) {
    this->hashes_ = hashes;
    this->number_of_bits_ = number_of_bits;
    this->number_of_requests_ = 0;
    this->number_of_false_positive_answers_ = 0;
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
    ++number_of_requests_;
    return result;
}
void BloomFilter::add(const std::string &obj) {
    for (size_t i = 0; i < hashes_; ++i) {
        bits_[getNHash(obj, i)] = 1;
    }
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
