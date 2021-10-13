#include <iostream>
using namespace std;
int GCD(int a, int b, int &number_of_calls);

bool IsInt(float number);

int GCDOfSequence(int number_of_numbers_in_sequence, int &number_of_calls);

int main(int argc, char *argv[]) {

    int number_of_numbers_in_sequence;
    int number_of_calls = 0;

    std::cin >> number_of_numbers_in_sequence;

    int answer = GCDOfSequence(number_of_numbers_in_sequence, number_of_calls);

    if (answer == -1) {
        std::cout << "Sequence has float values!";
    } else {
        std::cout << answer << ' ' << number_of_calls;
    }

    return 0;
}

int GCD(const int a, const int b, int &number_of_calls) {
    return (b == 0) ? std::abs(a) : GCD(b, a % b, ++number_of_calls);
}

int GCDOfSequence(int number_of_numbers_in_sequence, int &number_of_calls) {

    float first_value;
    std::cin >> first_value;

    if (!IsInt(first_value))
        return -1;

    for (int i = 1; i < number_of_numbers_in_sequence; ++i) {

        float second_value;
        std::cin >> second_value;

        if (IsInt(second_value)) {

            first_value = std::abs(GCD(first_value, second_value, number_of_calls));

        } else
            return -1;
    }

    return first_value;
}

bool IsInt(float number) {
    return number - static_cast<int>(number) < 0.000000001;
}
