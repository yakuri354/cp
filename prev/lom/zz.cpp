#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cmath>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <random>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <functional>

using namespace std;

map<char, long long> tmp;

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

int main() {
    tmp['a'] = 1;
    tmp['b'] = 5;
    tmp['c'] = 10;
    tmp['d'] = 50;
    tmp['e'] = 100;
    tmp['f'] = 200;
    tmp['g'] = 500;
    tmp['h'] = 1000;
    tmp['i'] = 2500;
    tmp['A'] = 5 * 100;
    tmp['B'] = 10 * 100;
    tmp['C'] = 50 * 100;
    tmp['D'] = 100 * 100;
    tmp['E'] = 200 * 100;
    tmp['F'] = 500 * 100;
    tmp['G'] = 1000 * 100;
    tmp['H'] = 2000 * 100;
    tmp['I'] = 5000 * 100;
    
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        long long nw = 0;
        for (auto c : s) {
            if (is_digit(c)) {
                nw *= 10;
                nw += (c - '0');
            } else {
                a[i] += tmp[c] * nw;
                nw = 0;
            }
        }
    }

    long long mx = 0, ans1 = 0, mn = 2e18, ans2 = 0;
    for (int i = 0; i < n; ++i) {
        if (mx <= a[i]) {
            mx = a[i];
            ans1 = i;
        }
        if (a[i] <= mn) {
            mn = a[i];
            ans2 = i;
        }
    }

    cout << min(ans1, ans2) + 1 << '\n' << max(ans1, ans2) + 1 << '\n';

    return 0;
}