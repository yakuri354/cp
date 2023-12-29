//
// Created by yakuri354 on 21.01.2022.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 21;

//bool mat[MAX_N][MAX_N];
bool discovered[MAX_N][MAX_N];
//bool discovered[MAX_N];
//int prevv[MAX_N];
//queue <int> qq;
queue<pair<int, int>> qq;

//int cum() {
//    int N;
//    cin >> N;
//
//    for (int i = 0; i < N; ++i)
//        for (int j = 0; j < N; ++j)
//            cin >> mat[i][j];
//
//    int A,B;
//    cin >> A >> B;
//
//    A--;
//    B--;
//
//    qq.push(A);
//    discovered[A] = true;
//
//    while (!qq.empty()) {
//        auto vv = qq.front();
//        qq.pop();
//
//
//        if (vv == B) {
//            vector<int> path{};
//            int i = B;
//            while (i != A) {
//                path.push_back(i);
//                i = prevv[i];
//            }
//            cout << path.size() << "\n";
//            path.push_back(A);
//            for (int j = path.size() - 1; j >= 0; --j) {
//                cout << path[j] + 1 << " ";
//            }
//            cout << "\n";
//            return 0;
//        }
//
//        for (int i = 0; i < N; ++i) {
//            if (mat[vv][i] && !discovered[i]) {
//                discovered[i] = true;
//                prevv[i] = vv;
//                qq.push(i);
//            }
//        }
//    }
//
//    cout << -1;
//}

int len[MAX_N][MAX_N];
pair<int, int> prevv[MAX_N][MAX_N];

int N;
int ll;

void aaa(int x, int y, pair<int, int> c) {
    if (x <= 0 || y <= 0 || x > N || y > N) return;
    if (!discovered[x][y]) {
        discovered[x][y] = true;
        len[x][y] = ll;
        prevv[x][y] = c;
        qq.emplace(x, y);
    }
}

int cumm() {
    int x1,y1,x2,y2;
    cin >> N >> x1 >> y1 >> x2 >> y2;

    pair<int, int> start(x1, y1);
    pair<int, int> target(x2, y2);

    qq.emplace(x1, y1);
    discovered[x1][y1] = true;

    while (!qq.empty()) {
        auto vv = qq.front();
        qq.pop();

        int x = vv.first, y = vv.second;

//        cerr << x << " " << y << " [" << len[x][y] << "]\n";

        if (vv == target) {
            cout << len[vv.first][vv.second] << endl;
            vector<pair<int, int>> path;
            while (vv != pair<int, int>(0, 0)) {
                path.push_back(vv);
                vv = prevv[vv.first][vv.second];
            }
            for (int j = path.size() - 1; j >= 0; --j) {
                cout << path[j].first << " " << path[j].second << "\n";
            }
            return 0;
        }

        ll = len[x][y] + 1;

        aaa(x + 2, y + 1, vv);
        aaa(x + 2, y - 1, vv);
        aaa(x - 2, y + 1, vv);
        aaa(x - 2, y - 1, vv);
        aaa(x + 1, y + 2, vv);
        aaa(x + 1, y - 2, vv);
        aaa(x - 1, y + 2, vv);
        aaa(x - 1, y - 2, vv);
    }
}