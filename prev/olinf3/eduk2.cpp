#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll maxn = 2 * 1e5;

int min1[maxn + 1];
int min2[maxn + 1];

int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        string s;
        ll zs = 0, ones = 0;
        cin >> s;
        for (auto x: s) {
            if (x == '1') ones++;
            else zs++;
        }
        min1[0] = 0;
        for (int i = 1; i < s.length(); ++i) {
            min1[i] = min1[i - 1] + s[i] == '0' ? -1 : 1;
        }
        min2[s.length() -1] = s[s.length() -1] == '0' ? -1 : 1;
        for (int i = s.length() - 2; i >= 0; --i) {
            min2[i] = min2[i + 1] + s[i] == '0' ? -1 : 1;
        }
        int minx = 0;
        for (int i = 0; i < s.length(); ++i) {
            for (int j = i; j < s.length(); ++j) {
                minx = min(minx, min1[i] + min2[j]);
            }
        }
        cout << ones - minx << '\n';
    }
}