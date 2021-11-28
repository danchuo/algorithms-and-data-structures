#include <iostream>

class SNMInt {
public:
    explicit SNMInt(int number) {
        number_ = number;
        sets_ = new int[number_];
        for (int i = 0; i < number_; ++i) {
            sets_[i] = i;
        }
        sizes_of_sets_ = new int[number_];
        for (int i = 0; i < number_; ++i) {
            sizes_of_sets_[i] = 1;
        }
    }

    ~SNMInt() {
        delete[] sets_;
        delete[] sizes_of_sets_;
    }

    int find(int input_set) {
        if (sets_[input_set] == input_set) {
            return input_set;
        }
        return sets_[input_set] = find(sets_[input_set]);
    }

    int unite(int first, int second) {
        first = find(first);
        second = find(second);
        if (first != second) {
            sets_[second] = first;
            sizes_of_sets_[first] += sizes_of_sets_[second];
            sizes_of_sets_[second] = 0;
        }
        return sizes_of_sets_[first];
    }

private:
    int *sizes_of_sets_;
    int *sets_;
    int number_;
};

int calculateMinimumNumberOfBridges(const int number_of_islands, const int number_of_bridges) {
    if (number_of_islands == 1) {
        return 0;
    }

    SNMInt *islands = new SNMInt(number_of_islands);

    int first_island;
    int second_island;

    for (int i = 0; i < number_of_bridges; ++i) {
        std::cin >> first_island >> second_island;
        if (islands->find(first_island) != islands->find(second_island)) {
            if (islands->unite(first_island, second_island) == number_of_islands) {
                delete islands;
                return (i + 1);
            }
        }
    }

    delete islands;
    return number_of_bridges;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_islands;
    int number_of_bridges;

    std::cin >> number_of_islands >> number_of_bridges;
    std::cout << calculateMinimumNumberOfBridges(number_of_islands, number_of_bridges);

    return 0;
}
