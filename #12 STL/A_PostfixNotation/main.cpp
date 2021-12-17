#include <iostream>
#include <stack>
#include <string>

std::string createPostfixNotation(std::string input) {
    std::string answer;
    answer.reserve(input.size());

    auto *stack = new std::stack<char>();

    char previous_symbol = '0';

    for (const auto &symbol : input) {
        if (symbol != ' ') {
            if (std::isdigit(symbol)) {
                if (!std::isdigit(previous_symbol) && !answer.empty()) {
                    answer += ' ';
                }
                answer += symbol;
            } else {
                if (symbol == '(') {
                    stack->push(symbol);
                } else {
                    if (symbol == ')') {
                        while (!stack->empty() && stack->top() != '(') {
                            answer += ' ';
                            answer += stack->top();
                            stack->pop();
                        }
                        if (stack->top() == '(') {
                            stack->pop();
                        }
                    } else {
                        while (!stack->empty() &&
                               (((symbol == '+' || symbol == '-') &&
                                 (stack->top() == '+' || stack->top() == '-')) ||
                                ((symbol == '+' || symbol == '-') &&
                                 (stack->top() == '/' || stack->top() == '*')))) {
                            answer += ' ';
                            answer += stack->top();
                            stack->pop();
                        }
                        stack->push(symbol);
                    }
                }
            }
        }
        previous_symbol = symbol;
    }

    while (!stack->empty()) {
        answer += ' ';
        answer += stack->top();
        stack->pop();
    }
    delete stack;

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string sequence;
    std::getline(std::cin, sequence);

    std::cout << createPostfixNotation(sequence) << '\n';

    return 0;
}
