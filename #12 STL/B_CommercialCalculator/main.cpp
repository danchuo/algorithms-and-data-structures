#include <iostream>
#include <set>

double findMinimal(std::multiset<double> *multiset) {
    double result = 0;

    while (multiset->size() > 1) {
        auto first = multiset->begin();
        auto second = next(first);
        auto third = next(second);
        auto sum = *first + *second;
        multiset->erase(first, third);
        result += sum * 0.05;
        multiset->insert(sum);
    }

    delete multiset;
    return result;
}

std::multiset<double> *fillMultiset(int amount) {
    std::multiset<double> *multiset = new std::multiset<double>();
    int input_number;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        multiset->insert(input_number);
    }

    return multiset;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    std::cin >> amount;
    printf("%.2lf", findMinimal(fillMultiset(amount)));

    return 0;
}
