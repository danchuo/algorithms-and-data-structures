#include <iostream>

double pow(double a, int n);

int main() {

    double a;
    int n;

    std::cin >> a;
    std::cin >> n;

    printf("%.5lf", pow(a, n));

    return 0;
}


double pow(double a, int n) {

    if (n == 0)
        return 1;
    if (n == 1)
        return a;
    if (n == 2)
        return a * a;

    if (n % 2 == 0) {
        double value = pow(a, n / 2);
        return value * value;
    }

    double value = pow(a, (n - 1) / 2);
    return value * value * a;


}
