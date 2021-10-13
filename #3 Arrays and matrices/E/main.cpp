#include <iostream>

int GetElementOfArrayAtPosition(int size, int first_element, int difference, int i, int j);

int64_t GetSumOfArray(int size, int first_element, int difference, int i, int j, int length);

int64_t GetSumOfOneRow(int size, int first_element, int difference, int i, int j, int length);

void DisplayArray(int size, int first_element, int difference);

int main() {
    int size;
    int first_element;
    int difference;
    std::cin >> size >> first_element >> difference;

    std::cout << GetSumOfArray(size, first_element, difference, 0, 1, size - 2) << '\n';

    if (size <= 20) {
        DisplayArray(size, first_element, difference);
    }
    return 0;
}

int64_t GetSumOfOneRow(int size, int first_element, int difference, int i, int j, int length) {
    int64_t sum = 0;

    for (int k = 0; k < length; ++k) {
        sum += GetElementOfArrayAtPosition(size, first_element, difference, i, j + k)
            + GetElementOfArrayAtPosition(size, first_element, difference, size - i - 1, j + k);
    }
    return sum;
}

int64_t GetSumOfArray(int size, int first_element, int difference, int i, int j, int length) {
    int64_t sum = 0;

    if (length > 0) {
        return GetSumOfOneRow(size, first_element, difference, i, j, length)
            + GetSumOfArray(size, first_element, difference, i + 1, j + 1, length - 2);
    }
    return sum;
}

void DisplayArray(int size, int first_element, int difference) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << GetElementOfArrayAtPosition(size, first_element, difference, i, j);

            if (j == size - 1) {
                if (i != size - 1) {
                    std::cout << '\n';
                }
            } else {
                std::cout << ' ';
            }
        }
    }
}

int GetElementOfArrayAtPosition(int size, int first_element, int difference, int i, int j) {
    int current_diagonal_line;
    int number_of_elements_on_current_diagonal_line;
    int number_of_elements_on_previous_diagonal_lines;
    int number_of_current_element;

    current_diagonal_line = i + j + 1;
    number_of_elements_on_current_diagonal_line =
        (current_diagonal_line <= size) ?
        current_diagonal_line :
        (size - (current_diagonal_line - size));
    number_of_elements_on_previous_diagonal_lines = 0;

    for (int k = 1; k < current_diagonal_line; ++k) {
        number_of_elements_on_previous_diagonal_lines += (k <= size) ? k : (size - (k - size));
    }

    number_of_current_element = number_of_elements_on_previous_diagonal_lines;
    int temp_second_iterator = -1;

    if (current_diagonal_line % 2 == 1) {
        number_of_current_element += number_of_elements_on_current_diagonal_line + 1;
    }

    for (int k = current_diagonal_line - 1; k > -1; --k) {
        for (int l = 0; l <= current_diagonal_line - 1; ++l) {
            if ((k + l) != (i + j)
                || (std::abs(k - l) > number_of_elements_on_current_diagonal_line - 1)) {
                continue;
            }

            if (current_diagonal_line % 2 == 0) {
                ++number_of_current_element;
            } else {
                --number_of_current_element;
            }

            if ((i == k) && (j == l) && (k + l) == (i + j)) {
                temp_second_iterator = l;
                break;
            }
        }
        if ((i == k) && (j == temp_second_iterator) && (k + temp_second_iterator) == (i + j)) {
            break;
        }
    }
    return first_element + difference * (number_of_current_element - 1);
}

