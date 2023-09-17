#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;

const ll MAX_N = 3e6 + 10;
ull powers[MAX_N];
ull factor = 31;

int fullRand() {
    return (((rand() << 15) + rand()) << 15) + rand();
}

struct DekTree {
    struct Node {
        bool key;
        ll priority;
        ll size;
        ull hsh;
        Node *left;
        Node *right;

        explicit Node(bool key) : key(key), priority(fullRand()), size(1), hsh(key * powers[0]), left(nullptr),
                                  right(nullptr) {}
    };

    Node *treeRoot = nullptr;

    typedef pair<Node *, Node *> KidPair;

    void insertByPos(ll pos, bool key) {
        auto [pref, suf] = splitByPos(treeRoot, pos);
        Node *newNode = new Node(key);
        treeRoot = merge(pref, merge(newNode, suf));
    }

    void eraseByPos(ll pos) {
        auto [prefWith, suf] = splitByPos(treeRoot, pos);
        auto [pref, X] = splitByPos(prefWith, pos - 1);
        treeRoot = merge(pref, suf);
    }

    ull getSegHash(ll l, ll r) {
        auto [prefSeg, suf] = splitByPos(treeRoot, r);
        auto [pref, seg] = splitByPos(prefSeg, l - 1);
        ll res = seg->hsh;
        treeRoot = merge(merge(pref, seg), suf);
        return res;
    }

    Node *merge(Node *left, Node *right) {
        if (!left) {
            return right;
        }

        if (!right) {
            return left;
        }

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            updateSize(left);
            updateSum(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            updateSize(right);
            updateSum(right);
            return right;
        }
    }

    KidPair splitByPos(Node *root, ll pos) {
        if (!root) {
            return {nullptr, nullptr};
        }

        if (getSize(root->left) + 1 <= pos) {
            KidPair kids = splitByPos(root->right, pos - getSize(root->left) - 1);
            root->right = kids.first;
            updateSize(root);
            updateSum(root);
            return {root, kids.second};
        } else {
            KidPair kids = splitByPos(root->left, pos);
            root->left = kids.second;
            updateSize(root);
            updateSum(root);
            return {kids.first, root};
        }
    }

    static ll getSize(Node *id) {
        return id ? id->size : 0;
    }

    static void updateSize(Node *id) {
        if (id) {
            id->size = getSize(id->left) + getSize(id->right) + 1;
        }
    }

    static ll getSum(Node *id) {
        return id ? id->hsh : 0;
    }

    static void updateSum(Node *id) {
        if (id) {
            id->hsh = id->key * powers[getSize(id->left)] + getSum(id->left) +
                      getSum(id->right) * powers[1 + getSize(id->left)];
        }
    }
};

void resolve() {
    string src;
    cin >> src;
    DekTree tree;
    for (int i = 0; i < ll(src.length()); ++i) {
        tree.insertByPos(i, src[i] - '0');
    }

    ll q;
    cin >> q;
    while (q--) {
        string type;
        cin >> type;
        if (type[0] == '?') {
            ll l1, l2, len;
            cin >> l1 >> l2 >> len;
            ull lHash = tree.getSegHash(l1, l1 + len - 1);
            ull rHash = tree.getSegHash(l2, l2 + len - 1);
            if (lHash == rHash) {
                cout << "ia\n";
            } else {
                cout << "jok\n";
            }
        } else {
            ll id;
            cin >> id;
            tree.eraseByPos(id);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    powers[0] = 1;
    for (ll i = 1; i < MAX_N; ++i) {
        powers[i] = powers[i - 1] * factor;
    }

    resolve();
    return 0;
}
