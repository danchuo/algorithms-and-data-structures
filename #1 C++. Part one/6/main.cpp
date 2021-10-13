#include <iostream>
#include <sstream>
#include <cmath>

double const Pi = 3.14159265;

int factorial(int x);

void SinX(double arr[], double x, double e);


double period(double x);

int main() {

    double x, e;
    std::cin >> x;
    std::cin >> e;

    double per = period(x);

    int sign = 1;

    while (std::abs(per) > Pi / 2) {

        if (per > 0) {
            per = Pi - per;
        } else {
            per += Pi;
            sign = -1 * sign;
        }
    }

    double arr[2] = {};

    SinX(arr, per, e);

    std::cout << (sign * (arr[0] - remainder(arr[0], e))) << "\n" << arr[1] << "\n";



    //  SinX2(arr, per, e);

    //  std::cout << (sign * (arr[0] - remainder(arr[0], e))) << "\n" << arr[1];
    return 0;
}

double period(double x) {

    double absX = std::abs(x);

    if (absX >= 2 * Pi) {

        while (absX >= 2 * Pi)
            absX -= 2 * Pi;
    }

    return x >= 0 ? absX : -absX;
}





void SinX(double arr[], double x, double e) {

    int i = 0;
    double sum = 0;
    double temp = x;
    do {
        i++;
        sum += temp;
        temp = (pow(-1, i) * pow(x, 2 * i + 1)) / (factorial(2 * i + 1));
    } while (std::abs(temp) > e);

    arr[0] = sum;
    arr[1] = i;
}

int factorial(int x) {
    if (x == 0)
        return 1;
    return (x > 1) ? (x * factorial(x - 1)) : x;
}

