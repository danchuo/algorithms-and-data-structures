#include <iostream>
#include <vector>

void FillArray(std::vector<int> *array);

int GetElementWithOffset(std::vector<int> const &array, int offset, int index);

int FindHammingDistance(std::vector<int> const &array, int offset);

int FindMaxHammingDistance(std::vector<int> const &input_array,
                           std::vector<int> *hamming_distance_for_every_offset);

void PrintAnswer(std::vector<int> const &input_array,
                 std::vector<int> const &hamming_distance_for_every_offset,
                 int max);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int length_of_array;
  std::cin >> length_of_array;

  std::vector<int> input_array(length_of_array);
  std::vector<int> hamming_distance_for_every_offset(length_of_array);

  FillArray(&input_array);

  int max = FindMaxHammingDistance(input_array, &hamming_distance_for_every_offset);

  PrintAnswer(input_array, hamming_distance_for_every_offset, max);

  return 0;
}

void PrintAnswer(std::vector<int> const &input_array,
                 std::vector<int> const &hamming_distance_for_every_offset,
                 int max) {
  int length_of_array = input_array.size();
  int lines_in_answer = length_of_array;
  std::cout << max << '\n';

  if (max == 0) {
    lines_in_answer = 1;
  }

  for (int i = 0; i < lines_in_answer; ++i) {
    if (hamming_distance_for_every_offset[i] == max) {
      for (int j = 0; j < length_of_array; ++j) {
        std::cout << GetElementWithOffset(input_array, i, j);

        if (j != length_of_array - 1) {
          std::cout << ' ';
        }
      }

      std::cout << "; " << i << '\n';
    }
  }
}

int FindMaxHammingDistance(std::vector<int> const &array,
                           std::vector<int> *hamming_distance_for_every_offset) {
  int max = 0;
  int size = array.size();

  for (int i = 0; i < size; ++i) {
    int current_offset = FindHammingDistance(array, i);

    if (current_offset > max) {
      max = current_offset;
    }

    hamming_distance_for_every_offset->at(i) = current_offset;
  }

  return max;
}

int FindHammingDistance(std::vector<int> const &array, int offset) {
  int distance = 0;
  int size = array.size();

  for (int i = 0; i < size; ++i) {
    if (array[i] != GetElementWithOffset(array, offset, i)) {
      ++distance;
    }
  }

  return distance;
}

int GetElementWithOffset(std::vector<int> const &array, int offset, int index) {
  return array[(index + array.size() - offset) % array.size()];
}

void FillArray(std::vector<int> *array) {
  for (int &element : *array) {
    std::cin >> element;
  }
}
