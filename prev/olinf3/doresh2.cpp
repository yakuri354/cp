// BEBRA
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 1e5;

bool merge(stack<pair<ll, ll>> &s) {
    auto fst = s.top();
    s.pop();
    auto snd = s.top();
    if (snd.second > fst.first) {
        s.pop();
        s.emplace(min(fst.first, snd.first), max(fst.second, snd.second));
        return true;
    } else {
        s.push(fst);
        return false;
    }
}

int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        ll N;
        cin >> N;
        stack<pair<ll, ll>> stack{};
        for (int i = 0; i < N; ++i) {
            ll x;
            cin >> x;
            stack.emplace(x, x);
            while (stack.size() > 1 && merge(stack));
        }
        cout << stack.size() << "\n";
    }
}