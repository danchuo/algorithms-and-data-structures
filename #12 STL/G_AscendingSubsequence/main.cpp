#include <iostream>
#include <set>

int findSequence(int amount) {
    std::multiset<int> multiset;

    int input_number;
    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        multiset.insert(input_number);
    }

    int max_length = 1;
    int current_length = 1;
    int previous_number = *multiset.begin();
    for (auto it = ++multiset.begin(); it != multiset.end(); ++it) {
        if (std::abs(*it - previous_number) == 1) {
            ++current_length;
        } else {
            current_length = 1;
        }

        if (current_length > max_length) {
            max_length = current_length;
        }
        previous_number = *it;
    }

    return max_length;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    std::cin >> amount;

    std::cout << findSequence(amount);

    return 0;
}
