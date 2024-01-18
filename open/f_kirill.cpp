#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<pair<int, int>, int> ans;

int ask(int v, int u) {
    if (ans.find({v, u}) != ans.end()) {
        return ans[{v, u}];
    }

    if (ans.find({u, v}) != ans.end()) {
        return ans[{u, v}];
    }

    cout << "? " << v + 1 << ' ' << u + 1 << endl;
    string res;
    cin >> res;
    if (res == "forward" || res == "f") {
        ans[{v, u}] = 1;
        ans[{u, v}] = 0;
    } else {
        ans[{v, u}] = 0;
        ans[{u, v}] = 1;
    }

    return res == "forward";
}

void solveTest() {
    ans.clear();

    int n;
    cin >> n;

    vector<int> d0;
    vector<int> d1;
    for (int i = 0; i < n; ++i) {
        d0.push_back(i);
    }

    vector<int> to(n);
    vector<int> inDeg(n);
    while (int(d0.size()) > 1) {
        int v = d0.back();
        d0.pop_back();
        int u = d0.back();
        d0.pop_back();
        int dir = ask(v, u);
        if (dir) {
            to[v] = u;
            ++inDeg[u];
            d1.push_back(v);
            d0.push_back(u);
        } else {
            to[u] = v;
            ++inDeg[v];
            d1.push_back(u);
            d0.push_back(v);
        }
    }

    vector<bool> bad(n);
    if (!d0.empty()) {
        int v = d0.back();
        int deg = 0;
        for (int i = 0; i < n; ++i) {
            if (i == v) {
                continue;
            }

            int dir = ask(v, i);
            if (dir) {
                ++inDeg[i];
            } else {
                ++inDeg[v];
            }

            deg += dir;
            if (!dir && to[i] != v) {
                bad[i] = true;
            }
        }

        if (deg <= 1) {
            cout << "! " << v + 1 << endl;
            return;
        }
    }

    vector<int> tmp;
    for (const auto& item : d1) {
        if (!bad[item]) {
            tmp.push_back(item);
        }
    }

    d1 = tmp;

    while (int(d1.size()) > 1) {
        int I = -1;
        int J = -1;
        sort(d1.begin(), d1.end(), [&](const int& v, const int& u) {
            return inDeg[v] > inDeg[u];
        });

        for (int i = 0; i < int(d1.size()); ++i) {
            for (int j = i + 1; j < int(d1.size()); ++j) {
                if (to[d1[i]] != d1[j] && to[d1[j]] != d1[i]) {
                    J = j;
                    break;
                }
            }

            if (J != -1) {
                I = i;
                break;
            }
        }

        if (I == -1) {
            break;
        }

        int v = d1[I];
        int u = d1[J];
        d1.erase(d1.begin() + J);
        d1.erase(d1.begin() + I);

        int dir = ask(v, u);
        if (dir) {
            ++inDeg[u];
            d1.push_back(u);
        } else {
            ++inDeg[v];
            d1.push_back(v);
        }
    }

    // check d1[0]
    while (!d1.empty()) {
        int v = d1.back();
        d1.pop_back();
        int deg = 0;
        for (int i = 0; i < n; ++i) {
            if (i == v) {
                continue;
            }

            if (ask(v, i)) {
                ++deg;
            }
        }

        if (deg <= 1) {
            cout << "! " << v + 1 << endl;
            return;
        }
    }

    cout << "! -1" << endl;
}

void solveSpecial() {
    ans.clear();

    int n;
    cin >> n;
    int V = 2;
    for (int i = 3; i < n; ++i) {
        if (ask(V, i)) {
            V = i;
        }
    }

    vector<int> d1;
    d1.push_back(0);
    d1.push_back(1);
    d1.push_back(V);
    while (!d1.empty()) {
        int v = d1.back();
        d1.pop_back();
        int deg = 0;
        for (int i = 0; i < n; ++i) {
            if (i == v) {
                continue;
            }

            int dir = ask(v, i);
            if (dir) {
                ++deg;
            }
        }

        if (deg <= 1) {
            cout << "! " << v + 1 << endl;
            return;
        }
    }

    cout << "! -1" << endl;
}

void resolve() {
    int type, testN;
    cin >> type >> testN;
    while (testN--) {
        if (type == 3) {
            solveSpecial();
        } else {
            solveTest();
        }

        string res;
        cin >> res;
        if (res == "WRONG") {
            exit(0);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    resolve();
    return 0;
}
