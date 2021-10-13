#include <iostream>

int ProcessingArray(int length_of_input_array);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int length_of_input_array;
  std::cin >> length_of_input_array;

  std::cout << ProcessingArray(length_of_input_array);

  return 0;
}
int ProcessingArray(int const length_of_input_array) {
  int number_of_multiplications = 0;
  int number_of_decreasing = 0;
  int number_of_increasing = 0;
  int number_of_multiplications_of_current_number;
  int current_number;

  for (int i = 0; i < length_of_input_array; ++i) {
    number_of_multiplications_of_current_number = 0;
    std::cin >> current_number;

    while (current_number != 0) {
      if (current_number % 2 == 0) {
        current_number /= 2;
        ++number_of_multiplications_of_current_number;
      }

      if ((current_number % 2 == 1) || (current_number % 2 == -1)) {
        if (current_number < 0) {
          ++current_number;
          ++number_of_increasing;
        } else {
          --current_number;
          ++number_of_decreasing;
        }
      }
    }

    if (number_of_multiplications_of_current_number > number_of_multiplications) {
      number_of_multiplications = number_of_multiplications_of_current_number;
    }
  }

  return number_of_decreasing + number_of_increasing + number_of_multiplications;
}
