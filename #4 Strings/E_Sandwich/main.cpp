#include <iostream>
#include <string>

int main() {
  std::string input_word;

  std::getline(std::cin, input_word);

  std::string_view input_word_view(input_word);
  input_word_view.remove_suffix(1);

  int length = input_word_view.length();
  for (int i = 0; i < length; i += 2) {
    std::cout << input_word_view[i];
  }

  for (int i = (length - 1) % 2 == 0 ? (length - 2) : (length - 1); i > 0; i -= 2) {
    std::cout << input_word_view[i];
  }

  return 0;
}
