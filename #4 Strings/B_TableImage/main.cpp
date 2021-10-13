#include <iostream>
#include <string>

void DrawTable(int number_of_rows);

void PrintBorder(std::string const &big, std::string const &small);

void PrintRods(std::string const &row);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number_of_rows;

  std::cin >> number_of_rows;

  DrawTable(number_of_rows);

  return 0;
}

void PrintRods(std::string const &row) {
  for (char i : row) {
    if (i == '+') {
      std::cout << '|';
    } else {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
}

void DrawTable(int number_of_rows) {
  int length_of_row;
  std::cin >> length_of_row;
  std::string previous_row = "+";

  for (int j = 0; j < length_of_row; ++j) {
    int length_of_cell;
    std::cin >> length_of_cell;
    for (int i = 0; i < length_of_cell; ++i) {
      previous_row += '-';
    }
    previous_row += '+';
  }

  std::cout << previous_row << '\n';
  std::string current_row;
  for (int i = 1; i <= number_of_rows; ++i) {
    PrintRods(previous_row);
    if (i == number_of_rows) {
      std::cout << previous_row;
      break;
    }
    std::cin >> length_of_row;
    current_row = "+";

    for (int j = 0; j < length_of_row; ++j) {
      int length_of_cell;
      std::cin >> length_of_cell;
      for (int i = 0; i < length_of_cell; ++i) {
        current_row += '-';
      }
      current_row += '+';
    }

    if (previous_row.length() > current_row.length()) {
      PrintBorder(previous_row, current_row);
    } else {
      PrintBorder(current_row, previous_row);
    }

    previous_row = current_row;
  }
}

void PrintBorder(std::string const &big, std::string const &small) {
  for (int j = 0; j < big.length(); ++j) {
    int l = small.length();
    if ((j < l) && ((big[j] == '+') || (small[j] == '+'))) {
      std::cout << '+';
    } else {
      std::cout << big[j];
    }
  }

  std::cout << '\n';
}
