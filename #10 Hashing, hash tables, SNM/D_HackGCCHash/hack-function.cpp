#include <iostream>
#include <unordered_set>
#include <string>
#include <ctime>
#include <cctype>
#include <random>
#include <cstring>
#include <set>
#include <fstream>

using std::string;

inline size_t
unaligned_load(const char *p) {
    size_t result;
    __builtin_memcpy(&result, p, sizeof(result));
    return result;
}

inline size_t
load_bytes(const char *p, int n) {
    size_t result = 0;
    --n;
    do
        result = (result << 8) + static_cast<unsigned char>(p[n]);
    while (--n >= 0);
    return result;
}

static const size_t mul = (((size_t) 0xc6a4a793UL) << 32UL) + (size_t) 0x5bd1e995UL;

size_t
Hash_bytes(const void *ptr, size_t len, size_t seed) {
    const char *const buf = static_cast<const char *>(ptr);

    // Remove the bytes not divisible by the sizeof(size_t).  This
    // allows the main loop to process the data as 64-bit integers.
    const size_t len_aligned = len & ~(size_t) 0x7;
    const char *const end = buf + len_aligned;
    size_t hash = seed ^ (len * mul);
    for (const char *p = buf; p != end; p += 8) {
        size_t v = unaligned_load(p) * mul;
        const size_t data = (v ^ (v >> 47)) * mul;
        hash ^= data;
        hash *= mul;
    }
    if ((len & 0x7) != 0) {
        const size_t data = load_bytes(end, len & 0x7);
        hash ^= data;
        hash *= mul;
    }
    size_t step1 = (hash >> 47);
    size_t step2 = hash ^ step1;

    hash = step2 * mul;

    step1 = (hash >> 47);

    hash = hash ^ step1;
    return hash;
}

bool checkUserName(uint64_t x) {
    for (int i = 0; i < 4; i++, x >>= 8) {
        unsigned char symbol = x;
        if (!islower(symbol) && !isdigit(symbol) && symbol != '_') {
            return false;
        }
    }
    return true;
}

uint64_t invert(uint64_t x) //inverse of process to generate k
{
    x *= mul;
    x ^= x >> 47;
    x *= mul;
    return x;
}

std::mt19937 rng(time(nullptr));
std::uniform_int_distribution<> dist(0, 62);

std::string createRandomString(int length) {
    string generated_string;
    for (int i = 0; i < length; i++) {
        int rand = dist(rng);
        if (rand < 26) {
            generated_string += rand + 'a';
        } else {
            if (rand < 52) {
                generated_string += rand % 26 + 'A';
            } else if (rand < 62) {
                generated_string += rand % 10 + '0';
            } else {
                generated_string += '_';
            }
        }
    }
    return generated_string;
}

std::set<string> generateCollisions(int number_of_collisions) {
    std::set<string> result;
    while (static_cast<int>(result.size()) < number_of_collisions) {
        string random_string = createRandomString(8);
        uint64_t inverted = invert(Hash_bytes(random_string.c_str(), 8, static_cast<size_t>(0xc70f6907UL))
                                       * mul);
        if (checkUserName(inverted)) {
            for (int i = 0; i < 4; i++, inverted >>= 8) {
                random_string += inverted & 0xffu;
            }

            result.insert(random_string);
        }
    }

    return result;
}

int main() {
    std::ofstream out_filestream("wrong_words.txt");

    for (const string &word: generateCollisions(15000)) {
        out_filestream << word << '\n';
    }

    return 0;
}
