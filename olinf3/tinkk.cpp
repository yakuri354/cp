//
// Created by lain on 9/11/22.
//

#include "bits/stdc++.h"

using namespace std;

int main() {
    string a;
    getline(cin, a);

    int lvl = 0;

    for (auto c: a) {
        if (c == '(') {
            if (lvl == 0) cout << '{';
            else if (lvl == 1) cout << '[';
            else cout << c;
            lvl++;
        } else if (c == ')') {
            if (lvl == 1) cout << '}';
            else if (lvl == 2) cout << ']';
            else cout << c;
            lvl--;
        } else {
            cout << c;
        }
    }
}