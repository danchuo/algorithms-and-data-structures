#include <iostream>

bool IsWordSpecialPalindrome(std::string const &word);

bool IsSymbolVowel(char const &symbol);

int main() {
  std::ios_base::sync_with_stdio(false);

  std::string input_word;
  std::cin >> input_word;

  if (IsWordSpecialPalindrome(input_word)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  return 0;
}

bool IsWordSpecialPalindrome(std::string const &word) {
  char first_consonant = 0;
  char second_consonant = 0;

  bool is_first_and_last_consonants_equal = false;

  for (char i : word) {
    if (!IsSymbolVowel(i)) {
      if (first_consonant == 0)
        first_consonant = i;
      else {
        second_consonant = i;
        break;
      }
    }
  }

  for (int i = static_cast<int>(word.length()) - 1; i > -1; --i) {
    if (!IsSymbolVowel(word[i])) {
      if (!is_first_and_last_consonants_equal) {
        if (first_consonant == word[i]) {
          is_first_and_last_consonants_equal = true;
        } else {
          return false;
        }
      } else {
        if (second_consonant == word[i]) {
          return true;
        } else {
          return false;
        }
      }
    }
  }

  return true;
}

bool IsSymbolVowel(char const &symbol) {
  auto code = static_cast<int>(symbol);
  return code == 97 || code == 101 || code == 105 || code == 111 || code == 117 || code == 121;
}