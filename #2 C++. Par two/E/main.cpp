#include <iostream>

char FindSymbol(std::string &first, std::string &second, int number_of_string, int position);

int main() {

    std::string first;
    std::string second;
    int number_of_string;
    int position;

    std::cin >> first >> second >> number_of_string >> position;

    std::cout << FindSymbol(first, second, number_of_string, position);

    return 0;
}

char FindSymbol(std::string &first, std::string &second, const int number_of_string, int position) {

    --position;

    if (number_of_string == 1)
        return first[position];

    if (number_of_string == 2)
        return second[position];

    for (int i = 3; i <= number_of_string; ++i) {

        if (i % 2 == 1) {
            first += second;
        } else {
            second += first;
        }

    }

    return (number_of_string % 2 == 1) ? first[position] : second[position];

}