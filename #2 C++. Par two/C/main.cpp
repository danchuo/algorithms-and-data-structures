#include <iostream>

bool IsPasswordSecure(std::string const &password);

int main() {

  std::string input_password;
  std::cin >> input_password;

  std::cout << (IsPasswordSecure(input_password) ? "YES" : "NO");

  return 0;
}

bool IsPasswordSecure(std::string const &password) {

  if (password.length() < 8)
    return false;

  bool is_any_lowercase = false;
  bool is_any_capital = false;
  bool is_any_number = false;

  for (char i: password) {

    if (i >= 'A' && i <= 'Z')
      is_any_capital = true;
    else if (i >= 'a' && i <= 'z')
      is_any_lowercase = true;
    else if (i >= '0' && i <= '9')
      is_any_number = true;

    if (is_any_lowercase && is_any_capital && is_any_number)
      return true;
  }

  return false;
}