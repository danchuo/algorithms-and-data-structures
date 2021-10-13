#include <iostream>
#include <string>
using std::string;

const int kSymbolsInAlphabet = 26;

string FindTheDifferences(string const &big, string const &small);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  string first;
  string second;

  std::getline(std::cin, first);
  std::getline(std::cin, second);

  if (first.length() > second.length()) {
    std::cout << FindTheDifferences(first, second);
  } else {
    std::cout << FindTheDifferences(second, first);
  }

  return 0;
}

string FindTheDifferences(string const &big, string const &small) {
  bool big_alphabet[kSymbolsInAlphabet]{false};
  bool small_alphabet[kSymbolsInAlphabet]{false};

  for (int i = 0; i < small.length(); ++i) {
    int first_char = big[i];
    int second_char = small[i];

    big_alphabet[first_char - 97] = true;
    small_alphabet[second_char - 97] = true;
  }

  for (int i = small.length(); i < big.length(); ++i) {
    int first_char = big[i];
    big_alphabet[first_char - 97] = true;
  }

  std::string answer;

  bool is_answer_ready = false;

  for (int i = 0; i < kSymbolsInAlphabet; ++i) {
    if (big_alphabet[i] ^ small_alphabet[i]) {
      answer += static_cast<char>(97 + i);
      answer += " ";
      is_answer_ready = true;
    }
  }

  if (!is_answer_ready) {
    return "NONE";
  }
  return answer;
}
