#include <iostream>
#include <string>

bool isPal(int input);

using namespace std;

int main() {

    int input, count;
    cin >> input;

    if (input < 10) {
        count = input;
    } else if (input < 100) {
        count = 9;
        if (input / 10 > input % 10)
            count += input / 10 - 1;
        else
            count += input / 10;

    } else if (input < 1000) {
        count = 18;

        if (input / 100 > input % 10) {
            count += (input / 100 - 1) * 10;
        } else {
            count += (input / 100) * 10 - (9 - input % 100 / 10);
        }

    } else {
        count = 108;

        for (int i = 1000; i <= input; i++) {
            if (isPal(i))
                count++;
        }
    }


    cout << count;
    return 0;
}

bool isPal(int input) {
    string str = to_string(input);

    for (int i = 0; i < str.length() / 2; i++) {
        if (str[i] != str[str.length() - 1 - i])
            return false;
    }
    return true;
}



