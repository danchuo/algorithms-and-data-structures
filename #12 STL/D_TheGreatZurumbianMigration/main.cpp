#include <iostream>
#include <vector>

std::vector<int> *fillPrices(int amount) {
    auto *vector = new std::vector<int>(amount);

    int input_number;
    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        vector->operator[](i) = input_number;
    }

    return vector;
}

std::vector<int> *fillCities(std::vector<int> *prices) {
    auto *final_cities = new std::vector<int>(prices->size(), -1);

    for (int i = 0; i < prices->size(); ++i) {
        for (int j = i + 1; j < prices->size(); ++j) {
            if (prices->at(j) < prices->at(i)) {
                final_cities->operator[](i) = j;
                break;
            }
        }
    }

    return final_cities;
}

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    std::cin >> amount;

    auto prices = fillPrices(amount);
    auto cities = fillCities(prices);

    printVector(cities);

    delete prices;
    delete cities;
    return 0;
}
