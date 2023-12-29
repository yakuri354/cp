//
// Created by yakuri354 on 18.02.2022.
//

#include <bits/stdc++.h>
#include "prettyprint.hpp"

using namespace std;

using ll = long long;
const ll N = 4, M = 4;
ll a[N][M];

int main() {
    srand(time(nullptr));

    vector<pair<ll, ll>> data{};

    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < M - 1; ++j) {
            data.emplace_back(i, j);
        }
    }

    cout << "STARTED\n\n\n\n\n\n\n";

    for (ll rep = 0;;rep++) {
        if (rep % 100 == 0) cout << "REP " << rep << endl;
        // obtain a time-based seed:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(data.begin(), data.end(), default_random_engine(seed));

        for (auto &[i, j]: data) {
            auto c = rand() % (M * N);
            a[i][j] = c;
            a[i + 1][j] = c;
            a[i][j + 1] = c;
            a[i + 1][j + 1] = c;
        }

        ofstream ofile("input.txt");
        ofile << N << " " << M << endl;
        for (auto &i: a) {
            for (long long j: i) {
                ofile << j << " ";
            }
            ofile << "\n";
        }
        ofile << flush;

        system("./D.out");
        ifstream ifile("output.txt");
        vector<tuple<ll, ll, ll>> data2;
        data2.reserve(N * M);
        ll X;
        ifile >> X;
        if (X == -1) {
            cerr << "\n-1 RECEIVED\n";

            cerr << "MISMATCH\nORIG:\n";
            for (auto &z:a) cout << z << "\n";
            cerr << "ORIGPATH:\n";
            cerr << data << endl;
            return 0;

            return 0;
        }
        for (int i = 0; i < X; ++i) {
            ll A, B, C;
            ifile >> A >> B >> C;
            data2.emplace_back(A, B, C);
        }
        vector<vector<ll>> a2(N, vector<ll>(M, -1));
        for (auto normalIterator = data2.rbegin(); normalIterator != data2.rend(); ++normalIterator) {
            auto [i, j, c] = *normalIterator;
            i -= 1;
            j -= 1;
            a2[i][j] = c;
            a2[i + 1][j] = c;
            a2[i][j + 1] = c;
            a2[i + 1][j + 1] = c;
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (a[i][j] != a2[i][j]) {
                    cerr << "\n\n\n\nMISMATCH\nORIG:\n";
                    for (auto &z:a) cout << z << "\n";
                    cerr << "\nGOT:\n";
                    for (auto &z:a2) cout << z << "\n";
                    cerr << "\nPATH:\n";
                    cerr << data2 << endl;
                    cerr << "\nORIGPATH:\n";
                    cerr << data << endl;
                    return 0;
                }
            }
        }
    }
}