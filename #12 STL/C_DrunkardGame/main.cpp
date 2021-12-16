#include <iostream>
#include <queue>
#include <string>

std::queue<int> *fillQueue(int amount) {
    auto *queue = new std::queue<int>();

    int number;
    for (int i = 0; i < amount; ++i) {
        std::cin >> number;
        queue->push(number);
    }

    return queue;
}

bool isFirstWin(int first_card, int second_card) {
    if (first_card == 0 && second_card == 9) {
        return true;
    } else if (first_card == 9 && second_card == 0) {
        return false;
    } else {
        return first_card > second_card;
    }
}

std::string findWinner(std::queue<int> *first, std::queue<int> *second) {
    int number_of_turn = 0;

    while (number_of_turn < 10e6 && !first->empty() && !second->empty()) {
        int first_card = first->front();
        int second_card = second->front();
        first->pop();
        second->pop();

        if (isFirstWin(first_card, second_card)) {
            first->push(first_card);
            first->push(second_card);
        } else {
            second->push(first_card);
            second->push(second_card);
        }

        ++number_of_turn;
    }

    if (first->empty()) {
        return "second " + std::to_string(number_of_turn);
    }

    if (second->empty()) {
        return "first " + std::to_string(number_of_turn);
    }

    return "botva";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_cards = 5;

    auto *first = fillQueue(number_of_cards);
    auto *second = fillQueue(number_of_cards);

    std::cout << findWinner(first, second);

    delete first;
    delete second;

    return 0;
}
