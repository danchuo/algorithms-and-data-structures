#include <iostream>

using namespace std;

void Rec(int n);

int main() {
    int n;
    cin >> n;
    Rec(n);

    return 0;
}

void Rec(int n) {
    if (n > 0) {

        int temp;
        cin >> temp;

        Rec(n - 1);
        cout << temp << " ";
    }
}