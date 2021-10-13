#include <iostream>
#include <vector>

void PrintPascalArray(int lines, int columns);

int main() {
    int lines;
    int columns;
    std::cin >> lines >> columns;
    PrintPascalArray(lines, columns);
    return 0;
}

void PrintPascalArray(int lines, int columns) {
    std::vector<int64_t> top_line(columns, 1);

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (i == 0 || j == 0) {
                std::cout << 1;
            } else {
                int64_t current_number = top_line[j - 1] + top_line[j];
                std::cout << current_number;

                top_line[j] = current_number;
            }

            if ((j == columns - 1) && (i != lines - 1)) {
                std::cout << '\n';
            } else {
                std::cout << ' ';
            }
        }
    }
}
