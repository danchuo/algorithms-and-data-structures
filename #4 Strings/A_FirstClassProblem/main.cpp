#include <iostream>
#include <string>

std::string GenerateNextRow(std::string const &previous_row);

std::string GenerateNthRow(std::string const &first_row, int nth_row);

int main() {
  std::string first_row;
  int nth_row;
  std::cin >> first_row >> nth_row;

  std::cout << GenerateNthRow(first_row, nth_row);

  return 0;
}

std::string GenerateNthRow(std::string const &first_row, int const nth_row) {
  std::string current_row = first_row;

  for (int i = 2; i <= nth_row; ++i) {
    current_row = GenerateNextRow(current_row);
  }

  return current_row;
}

std::string GenerateNextRow(std::string const &previous_row) {
  std::string current_row;
  char current_symbol = previous_row[0];
  int number_of_current_symbols = 0;

  for (char i : previous_row) {
    if (i == current_symbol) {
      ++number_of_current_symbols;
    } else {
      current_row += std::to_string(number_of_current_symbols) + current_symbol;
      current_symbol = i;
      number_of_current_symbols = 1;
    }
  }
  current_row += std::to_string(number_of_current_symbols) + current_symbol;

  return current_row;
}

