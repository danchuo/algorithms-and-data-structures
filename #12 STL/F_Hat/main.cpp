#include <iostream>
#include <map>
#include <string>

void processCommands(int number_of_commands, int number_of_attempts) {
    std::map<std::string, int> words;
    std::map<int, int> score;

    for (int i = 0; i < number_of_commands; ++i) {
        score[i + 1] = 1;
    }

    int team_number;
    std::string input_word;

    for (int i = 0; i < number_of_attempts; ++i) {
        std::cin >> team_number >> input_word;

        if (words[input_word] != 0) {
            --score[words[input_word]];
            words[input_word] = team_number;
            ++score[team_number];
        } else {
            ++score[team_number];
            words[input_word] = team_number;
        }
    }

    for (const auto &pair : score) {
        std::cout << pair.second - 1 << ' ';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_commands;
    int number_of_attempts;

    std::cin >> number_of_commands;
    std::cin >> number_of_attempts;

    processCommands(number_of_commands, number_of_attempts);

    return 0;
}
