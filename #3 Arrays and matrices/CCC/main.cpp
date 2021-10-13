#include <iostream>
#include <vector>
#include <cmath>

int ServiceRequest(std::vector<int> *array, std::vector<int> *blocks, int left, int right);

void FillArrays(std::vector<int> *array, std::vector<int> *blocks, int length_of_block);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int numbers;
  int number_of_requests;
  std::cin >> numbers;

  std::vector<int> array(numbers, -1);
  int number_of_blocks = ceil(sqrt(numbers));
  std::vector<int> blocks(number_of_blocks, 0);

  FillArrays(&array, &blocks, sqrt(numbers));

  std::cin >> number_of_requests;

  for (int i = 0; i < number_of_requests; ++i) {
    int left;
    int right;
    std::cin >> left >> right;

    std::cout << ServiceRequest(&array, &blocks, left, right) << ' ';
  }

  return 0;
}

int ServiceRequest(std::vector<int> *array, std::vector<int> *blocks, int left, int right) {
  --left;
  --right;
  int length_of_block = sqrt(array->size());
  int sum = 0;

  for (int i = left; i <= right; ++i) {
    if ((i % length_of_block == 0) && (i + length_of_block - 1 <= right)) {
      sum += blocks->at(i / length_of_block);
      i += length_of_block - 1;
    } else {
      if (array->at(i) == 0) {
        ++sum;
      }
    }
  }
  return sum;
}

void FillArrays(std::vector<int> *array, std::vector<int> *blocks, int const length_of_block) {
  int input_number;

  for (int i = 0; i < array->size(); ++i) {
    std::cin >> input_number;
    array->at(i) = input_number;

    if (input_number == 0) {
      blocks->at(i / length_of_block)++;
    }
  }
}
