#include <iostream>

int **FillTwoDimensionalArray(int rows, int columns);

void DisplayInvertedArray(int rows, int columns, int **array);

int main() {
    int rows;
    int columns;
    std::cin >> rows >> columns;
    int **array = FillTwoDimensionalArray(rows, columns);

    DisplayInvertedArray(rows, columns, array);

    return 0;
}

int **FillTwoDimensionalArray(int const rows, int const columns) {
    int **array;
    array = new int *[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new int[columns];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cin >> array[i][j];
        }
    }
    return array;
}

void DisplayInvertedArray(int rows, int columns, int **array) {
    std::cout << columns << ' ' << rows << '\n';

    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            std::cout << array[rows - j - 1][i];

            if (j == rows - 1) {
                if (i != columns - 1) {
                    std::cout << '\n';
                }
            } else {
                std::cout << ' ';
            }
        }
    }
}
