#include <iostream>

class SNMInt {
public:
    explicit SNMInt(int number) {
        number_ = number;
        sets_ = new int[number_];
        for (int i = 0; i < number_; ++i) {
            sets_[i] = i;
        }
    }

    ~SNMInt() {
        delete[] sets_;
    }

    int find(int input_set) {
        if (sets_[input_set] == input_set) {
            return input_set;
        }
        return sets_[input_set] = find(sets_[input_set]);
    }

    void unite(int first, int second) {
        first = find(first);
        second = find(second);
        if (first != second) {
            sets_[second] = first;
        }
    }

    bool areEqual() {
        int first = sets_[0];
        for (int i = 1; i < number_; ++i) {
            if (sets_[i] != first) {
                return false;
            }
        }
        return true;
    }

private:
    int *sets_;
    int number_;
};

int calculateMinimumNumberOfBridges(const int number_of_islands, const int number_of_bridges) {
    if (number_of_islands == 1) {
        return 1;
    }

    SNMInt *islands = new SNMInt(number_of_islands);

    int first_island;
    int second_island;

    for (int i = 0; i < number_of_bridges; ++i) {
        std::cin >> first_island >> second_island;

        if (islands->find(first_island) != islands->find(second_island)) {
            islands->unite(first_island, second_island);
            if (islands->areEqual()) {
                delete islands;
                return (i + 1);
            }
        }
    }

    delete islands;
    return 0;
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
