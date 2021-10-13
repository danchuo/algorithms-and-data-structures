#include <iostream>

using namespace std;

bool Compare(string s1, string s2);

int main() {
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    cout << (Compare(s1, s2) ? "yes" : "no");

    return 0;
}

bool Compare(string s1, string s2) {

    if (s1.length() != s2.length())
        return false;

    int rnd = rand() % s1.length();
    if (s1[rnd] != s2[rnd])
        return false;

    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i])
            return false;
    }

    return true;
}

