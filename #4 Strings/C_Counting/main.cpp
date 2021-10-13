#include <iostream>
#include <string>
using std::string;

int HowManyWordsInString(string const &counting);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  string input_counting;
  string names;

  std::getline(std::cin, input_counting);
  std::getline(std::cin, names);

  int words_in_counting = HowManyWordsInString(input_counting);
  int number_of_names = HowManyWordsInString(names);
  int number_of_child;

  if ((words_in_counting > number_of_names) && (words_in_counting % number_of_names == 0)
      || words_in_counting == number_of_names) {
    number_of_child = number_of_names;
  } else {
    number_of_child = words_in_counting % number_of_names;
  }

  string answer;
  int number_of_words = 1;

  for (int i = 0; i < names.length(); ++i) {
    if (names[i] == ' ') {
      ++number_of_words;
    }

    if (number_of_words == number_of_child) {
      if (number_of_words != 1) {
        ++i;
      }
      while ((names[i] != ' ') && (names[i] != '\0')) {
        answer += names[i];
        ++i;
      }

      break;
    }
  }

  std::cout << answer;

  return 0;
}

int HowManyWordsInString(string const &counting) {
  int number_of_words = 1;
  for (char i : counting) {
    if (i == ' ') {
      ++number_of_words;
    }
  }

  return number_of_words;
}

