#include <iostream>

int main() {
    double a, sum, count;

    std::cin >> a;

    while (a != 0) {
        sum += a;
        count++;
        std::cin >> a;
    }

    printf("%.5lf", sum / count);

    return 0;
}
