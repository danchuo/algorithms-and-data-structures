#include <iostream>
#include <set>

void processCommands(const int number_of_commands) {
    auto *multiset = new std::multiset<int>();
    int mod = 1000000000;
    int last_request_result = -1;
    char request;
    int input_number;

    for (int command = 0; command < number_of_commands; ++command) {
        std::cin >> request;
        std::cin >> input_number;

        if (request == '+') {
            if (last_request_result != -1) {
                multiset->insert((input_number % mod + last_request_result % mod) % mod);
            } else {
                multiset->insert(input_number);
            }
            last_request_result = -1;
        } else {
            auto result = multiset->lower_bound(input_number);

            if (result == multiset->end()) {
                last_request_result = -1;
            } else {
                last_request_result = *result;
            }
            std::cout << last_request_result << '\n';
        }
    }

    delete multiset;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_commands;
    std::cin >> number_of_commands;

    processCommands(number_of_commands);

    return 0;
}
