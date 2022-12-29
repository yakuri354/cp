//
// Created by yakuri354 on 21.01.2022.
//
#define _LIBCPP_DEBUG 1

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 100;

bool discovered[MAX_N][MAX_N];
int len[MAX_N][MAX_N];
queue<pair<int, int>> qq;
char field[MAX_N][MAX_N];

int N, M;

void disc(int x, int y, int ll, int xoff, int yoff) {
    int maxxoff = 0;
    int maxyoff = 0;
    while (y + maxyoff + yoff < N && x + xoff + maxxoff < M && y + maxyoff + yoff >= 0 && x + xoff + maxxoff >= 0 &&
           field[x + maxxoff + xoff][y + maxyoff + yoff] == 0) {
        maxxoff += xoff;
        maxyoff += yoff;
    }

    if (maxxoff != 0 || maxyoff != 0) {
        if (!discovered[x + maxxoff][y + maxyoff]) {
            len[x + maxxoff][y + maxyoff] = ll;
            discovered[x + maxxoff][y + maxyoff] = true;
            qq.emplace(x + maxxoff, y + maxyoff);
        }
    }
}

int main() {
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            int a;
            cin >> a;
            field[j][i] = a;
        }

    qq.emplace(0, 0);
    discovered[0][0] = true;

    if (field[0][0] == 2) {
        cout << 0;
        return 0;
    }

    while (!qq.empty()) {
        auto vv = qq.front();
        qq.pop();

//        cout << "Walked in " << vv.first << " " << vv.second << endl;

        if (field[vv.first][vv.second] == 2) {
            cout << len[vv.first][vv.second];
            return 0;
        }

        int ll = len[vv.first][vv.second] + 1;

        disc(vv.first, vv.second, ll, 1, 0);
        disc(vv.first, vv.second, ll, -1, 0);
        disc(vv.first, vv.second, ll, 0, 1);
        disc(vv.first, vv.second, ll, 0, -1);
    }
}

//14 12
//1 1 1 1 0 0 0 0 0 0 0 0
//1 1 0 0 0 0 0 0 0 0 1 1
//1 1 0 1 1 1 1 1 1 1 1 1
//2 1 0 1 0 0 0 0 0 0 0 0

//14 12
//0 0 0 0 0 0 0 0 0 0 1 1
//1 1 0 0 0 0 0 0 0 0 1 1
//1 1 0 1 1 1 1 1 1 1 1 1
//2 1 0 1 0 0 0 0 0 0 0 0
//0 1 0 1 0 0 0 0 0 0 0 0
//0 1 0 1 0 0 0 0 0 0 0 0
//0 1 0 1 0 0 0 0 0 0 0 0
//0 1 0 1 1 1 1 1 1 1 1 1
//0 1 0 0 0 0 0 0 0 0 0 1
//0 1 1 1 1 1 1 1 1 1 2 1
//1 1 1 1 1 1 1 1 1 1 1 1
//1 1 1 1 1 1 1 1 1 1 1 1
//1 1 1 1 1 1 1 1 1 1 1 1
//1 1 1 1 1 1 1 1 1 1 1 1