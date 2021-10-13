#include <iostream>

int PowerOfTwo(int64_t number);

int main() {

  int64_t input_number;
  std::cin >> input_number;

  std::cout << PowerOfTwo(input_number);

  return 0;
}

int PowerOfTwo(int64_t number) {

  int number_of_divisions = 0;

  int64_t two = 0;

  while ((two = two == 0 ? 1 : two * 2) < number) {
    ++number_of_divisions;
  }

  return number_of_divisions;

}