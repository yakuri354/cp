#include <iostream>
#include "testlib.h"

using namespace std;

int n, k, a[100][100], was[100][100], timer = 0;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool Valid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

int killed = 0;

bool DfsIsDead(int x, int y, int c) {
    was[x][y] = timer;
    killed++;
    bool is_dead = true;
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (Valid(nx, ny) && a[nx][ny] == c && was[nx][ny] != timer) {
            is_dead &= DfsIsDead(nx, ny, c);
        }
        if (Valid(nx, ny) && !a[nx][ny]) {
            is_dead = false;
        }
    }
    return is_dead;
}

void DfsKill(int x, int y, int c) {
    a[x][y] = 0;
    killed++;
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (Valid(nx, ny) && a[nx][ny] == c) {
            DfsKill(nx, ny, c);
        }
    }
}

void Clear() {
    timer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            was[i][j] = 0;
        }
    }
}

int GetAns(InStream &in) {
    int m = in.readInt(1, k, "m");
    for (int i = 0; i < m; ++i) {
        int x = in.readInt(1, n, "x"), y = in.readInt(1, n, "y");
        x--;
        y--;
        ensuref(a[x][y] == 0, "the cell is not free");
        a[x][y] = 2;
    }

    Clear();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 2 && !was[i][j]) {
                timer++;
                if (DfsIsDead(i, j, 2)) {
                    DfsKill(i, j, 2);
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 1 && !was[i][j]) {
                timer++;
                killed = 0;
                if (DfsIsDead(i, j, 1)) {
                    result += killed;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 2) {
                a[i][j] = 0;
            }
        }
    }

    return result;
}

long double GetScore(int part_ans, int jury_ans) {
    if (part_ans > jury_ans) {
        return 1;
    }
    long double d = (long double)part_ans / jury_ans;
    return d * d * d * d * d * d * d;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    long double score = 0;
    while (t--) {
        n = inf.readInt();
        k = inf.readInt();
        Clear();
        inf.readEoln();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                char c = inf.readChar();
                a[i][j] = (c == '*');
            }
            inf.readEoln();
        }
        int jury_ans = GetAns(ans);
        int part_ans = GetAns(ouf);
        score += GetScore(part_ans, jury_ans) * 10;
    }
    quitp(score, "Success");
}
