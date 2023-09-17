#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAX_N = 3e5;
const ll MOD = 998244353;

ll dp[MAX_N];
ll src[MAX_N];

class SegTree {
private:
    vector<ll> tree;
    vector<ll> treeSm;
    vector<ll> treeFt;
    int sz;

    void setFact(int root, int l, int r, int sL, int sR, ll val) {
        push(root, l, r);
        if (l > sR || r < sL) {
            return;
        }

        if (sL <= l && r <= sR) {
            treeFt[root] = val;
            push(root, l, r);
            return;
        }

        int m = (l + r) >> 1;
        int lRoot = (root << 1) + 1;
        int rRoot = (root << 1) + 2;
        setFact(lRoot, l, m, sL, sR, val);
        setFact(rRoot, m + 1, r, sL, sR, val);

        treeSm[root] = (treeSm[lRoot] + treeSm[rRoot]) % MOD;
        tree[root] = (tree[lRoot] + tree[rRoot]) % MOD;
    }

    void setVal(int root, int l, int r, int pos, ll val) {
        push(root, l, r);

        if (l == r) {
            treeSm[root] = val;
            tree[root] = (treeSm[root] * treeFt[root]) % MOD;
            return;
        }

        int m = (l + r) >> 1;
        int lRoot = (root << 1) + 1;
        int rRoot = (root << 1) + 2;
        if (pos <= m) {
            setVal(lRoot, l, m, pos, val);
        } else {
            setVal(rRoot, m + 1, r, pos, val);
        }

        treeSm[root] = (treeSm[lRoot] + treeSm[rRoot]) % MOD;
        tree[root] = (tree[lRoot] + tree[rRoot]) % MOD;
    }

    ll get(int root, int l, int r, int sL, int sR) {
        push(root, l, r);
        if (l > sR || r < sL) {
            return 0;
        }

        if (sL <= l && r <= sR) {
            return tree[root];
        }

        int m = (l + r) >> 1;
        int lRoot = (root << 1) + 1;
        int rRoot = (root << 1) + 2;
        return (get(lRoot, l, m, sL, sR) + get(rRoot, m + 1, r, sL, sR)) % MOD;
    }

    void push(int root, int l, int r) {
        if (treeFt[root] == -1) {
            return;
        }

        tree[root] = (treeSm[root] * treeFt[root]) % MOD;
        if (l == r) {
            return;
        }

        if (l < r) {
            ll lRoot = (root << 1) + 1;
            ll rRoot = (root << 1) + 2;
            treeFt[lRoot] = treeFt[root];
            treeFt[rRoot] = treeFt[root];
        }

        treeFt[root] = -1;
    }

public:
    explicit SegTree(int sz) : sz(sz) {
        tree.resize(sz << 2, 0);
        treeSm.resize(sz << 2, 0);
        treeFt.resize(sz << 2, -1);
    }

    void setVal(int pos, ll val) {
        cout << "set " << pos << " to " << val << endl;
        setVal(0, 0, sz - 1, pos, val);
    }

    void setFact(int l, int r, ll val) {
        cout << "set_fac from " << l << " to " << r << " *= " << val << endl;
        setFact(0, 0, sz - 1, l, r, val);
        cout << "t = ";
        for (ll i : tree) {
            cout << i << ' ';
        }
        cout << endl;
        cout << "s = ";
        for (ll i : treeSm) {
            cout << i << ' ';
        }
        cout << endl;
        cout << "f = ";
        for (ll i : treeFt) {
            cout << i << ' ';
        }
        cout << endl;
    }

    ll get(int l, int r) {
        ll ans = get(0, 0, sz - 1, l, r);
        cout << "sum from " << l << " to " << r << " = " << ans << endl;
        return ans;
    }
};

void resolve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> src[i];
    }

    ll totMn = src[0];
    ll totMx = src[0];
    SegTree treeMn(n + 1);
    SegTree treeMx(n + 1);
    vector<int> stackMn;
    vector<int> stackMx;
    stackMn.push_back(-1);
    stackMn.push_back(0);
    stackMx.push_back(-1);
    stackMx.push_back(0);
    for (int i = 1; i < n; ++i) {
        while (stackMn.back() != -1 && src[stackMn.back()] > src[i]) {
            stackMn.pop_back();
        }

        while (stackMx.back() != -1 && src[stackMx.back()] < src[i]) {
            stackMx.pop_back();
        }

        totMn = min(totMn, src[i]);
        totMx = max(totMx, src[i]);
        treeMn.setFact(stackMn.back() + 1, i, src[i]);
        treeMx.setFact(stackMx.back() + 1, i, src[i]);
        ll mx = treeMx.get(1, i);
        ll mn = treeMn.get(1, i);
        dp[i] = ((totMx - totMn + mx - mn) + MOD) % MOD;
        treeMn.setVal(i + 1, dp[i]);
        treeMx.setVal(i + 1, dp[i]);

        stackMn.push_back(i);
        stackMx.push_back(i);
    }

    cout << dp[n - 1] << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
