#include <iostream>
#include <deque>
#include <string>

std::deque<int> *fillQueue(int amount) {
    auto *deque = new std::deque<int>();

    int number;
    for (int i = 0; i < amount; ++i) {
        std::cin >> number;
        deque->push_back(number);
    }

    return deque;
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

std::string findWinner(std::deque<int> *first, std::deque<int> *second) {
    int number_of_turn = 0;

    while (number_of_turn < 10e6 && !first->empty() && !second->empty()) {
        if (isFirstWin(first->front(), second->front())) {
            first->push_back(second->front());
            first->push_back(first->front());
            first->pop_front();
            second->pop_front();
        } else {
            second->push_back(first->front());
            second->push_back(second->front());
            second->pop_front();
            first->pop_front();
        }

        ++number_of_turn;
    }

    if (number_of_turn == 10e6) {
        return "botva";
    }

    if (first->empty()) {
        return "second " + std::to_string(number_of_turn);
    }

    return "first " + std::to_string(number_of_turn);
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
