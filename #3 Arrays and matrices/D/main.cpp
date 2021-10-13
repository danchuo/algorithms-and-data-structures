#include <iostream>
#include <vector>
#include <deque>

void SuperMinimum(int numbers, int period);

void DequePushBack(std::deque<int> *deque, int element);

int main() {
  int numbers;
  int period;
  std::cin >> numbers >> period;
  SuperMinimum(numbers, period);

  return 0;
}

void DequePushBack(std::deque<int> *deque, int element) {
  while (!deque->empty() && (element < deque->back())) {
    deque->pop_back();
  }

  deque->push_back(element);
}

void SuperMinimum(int const numbers, int const period) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::deque<int> current_minimums;
  std::vector<int> current_period_elements(period);

  int current_number_in_period = 0;

  for (int i = 0; i < period; ++i) {
    std::cin >> current_period_elements[i];

    DequePushBack(&current_minimums, current_period_elements[i]);
  }

  std::cout << current_minimums.front() << ' ';

  for (int i = 0; i < numbers - period; ++i) {
    if (current_period_elements[current_number_in_period % period] == current_minimums.front()) {
      current_minimums.pop_front();
    }

    std::cin >> current_period_elements[current_number_in_period % period];

    DequePushBack(&current_minimums, current_period_elements[current_number_in_period % period]);

    ++current_number_in_period;
    std::cout << current_minimums.front() << ' ';
  }
}
