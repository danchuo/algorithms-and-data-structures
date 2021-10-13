#include <iostream>
#include <string>

using std::string;
using std::string_view;

bool isDigit(char symbol) {
    return ((symbol == '0') || (symbol == '1') || (symbol == '2') ||
        (symbol == '3') || (symbol == '4') ||
        (symbol == '5') || (symbol == '6') || (symbol == '7') ||
        (symbol == '8') || (symbol == '9'));
}

string unpackString(string const &input_string) {
    string answer;

    for (int i = 0; i < input_string.length(); ++i) {
        if (isDigit(input_string[i])) {
            int k;
            int number = input_string[i] - '0';
            string part_of_answer;
            if (number > 0) {
                k = i + 1;
                int number_of_close_brackets = 0;
                int number_of_open_brackets = 1;

                while (number_of_close_brackets != number_of_open_brackets) {
                    ++k;
                    if (input_string[k] == ']') {
                        ++number_of_close_brackets;
                    } else if (input_string[k] == '[') {
                        ++number_of_open_brackets;
                    }
                }

                string next_step = input_string.substr(i + 2,
                                                       k - 2 - i);
                part_of_answer = unpackString(next_step);
            }

            for (int j = 0; j < number; ++j) {
                answer += part_of_answer;
            }

            i = k;
        } else {
            answer += input_string[i];
        }
    }

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    string sequence;
    std::getline(std::cin, sequence);

    std::cout << unpackString(sequence);

    return 0;
}



