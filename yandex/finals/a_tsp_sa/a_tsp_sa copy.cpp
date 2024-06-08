// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <chrono>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

#ifndef DBG
#define cerr if (0) cerr
#endif

using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

inline bool decide(fl t, mt19937_64 &mt, ll old_s, ll new_s) {
    if (new_s < old_s) return true;

    fl r = uniform_real_distribution<fl>()(mt);
    return r < exp(fl(old_s - new_s) / t);
    // return r < exp(-(fl(old_s) / fl(new_s)) / t);

    // return r < exp(fl(log(old_s) - log(new_s)) / t);
}

inline fl update_temp(fl t, ll it) {
    // return 50 / log(1 + it);
    return t * 0.999999999;
}

void solve(bool from_global) {
    const ll n = 312;

    ll global_len = 0;
    vector<ll> global(n);

    {
        ifstream inp("ans.txt");
        if (!inp.good()) exit(-1);
        for (ll i = 0; i < n; i++) {
            inp >> global[i];
        }
    }

    vector<vector<ll>> mat(n, vector<ll>(n));

    ifstream edges("mat.txt");

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            edges >> mat[i][j];
        }
    }

    for (ll i = 0; i < n - 1; i++) {
        global_len += mat[global[i]][global[i+1]];
    }

    cout << "STARTING WITH GL " << global_len << endl << endl;

    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

    ll cur_l = 0;
    vector<ll> state(n);

    if (from_global) {
        state = global;
        cur_l = global_len;   
    } else {
        iota(state.begin(), state.end(), 0);
        shuffle(state.begin(), state.end(), mt);
        
        for (ll i = 0; i < n - 1; i++) {
            cur_l += mat[state[i]][state[i+1]];
        }
    }

    fl temp = 10;

    uniform_int_distribution<ll> nd(0, n - 1);

    for (ll it = 1;; it++) {
        if (it % 10000 == 0) {
            cout << "\33[2K\r" << "gl " << global_len << " t " << temp << " cur " << cur_l << flush;
        }

        ll i = nd(mt);
        ll j = nd(mt);
        while (j == i) j = nd(mt);

        if (i > j) swap(i, j);

        ll new_l = cur_l;

        if (j == i + 1) {
            new_l -= mat[state[i]][state[j]];
            new_l += mat[state[j]][state[i]];

            if (i > 0) new_l += -mat[state[i-1]][state[i]] + mat[state[i-1]][state[j]];
            if (j < n - 1) new_l += -mat[state[j]][state[j+1]] + mat[state[i]][state[j+1]];
        } else {
            if (i > 0) new_l += -mat[state[i-1]][state[i]] + mat[state[i-1]][state[j]];
            if (i < n - 1) new_l += -mat[state[i]][state[i+1]] + mat[state[j]][state[i+1]];

            if (j > 0) new_l += -mat[state[j-1]][state[j]] + mat[state[j-1]][state[i]];
            if (j < n - 1) new_l += -mat[state[j]][state[j+1]] + mat[state[i]][state[j+1]];
        }

        if (decide(temp, mt, cur_l, new_l)) {
            swap(state[i], state[j]);
            cur_l = new_l;
        }

        if (cur_l < global_len) {
            cout << "------ NEW GLOBAL ------" << endl;
            cout << global_len << endl << endl << endl;

            global = state;
            global_len = cur_l;

            system("touch ans.txt");

            ofstream of("ans.txt", ios::trunc);
            
            if (of.bad()) exit(-1);

            for (ll i = 0; i < n; i++) {
                of << global[i] << ' ';
            }

            of << flush;
        }

        temp = update_temp(temp, it);
    }

    cout << endl;
}

// int main(int argc, char **argv) {
//     cin.tie(nullptr);
//     ios::sync_with_stdio(false);
//     // ll t; cin >> t; while (t --> 0)
//     bool fg = false;
//     for (ll i = 1; i < argc; i++) {
//         if (string(argv[i]) == "--from-global") {
//             fg = true;
//         }
//     }
//     solve(fg);
// }

int main() {
    // cout << "4 308 58 304 35 166 217 172 247 81 44 145 160 106 26 254 215 30 91 227 165 232 221 80 269 78 277 248 278 268 184 190 136 23 196 281 41 114 85 60 1 46 309 200 266 296 311 65 70 113 153 88 191 34 174 55 121 99 29 169 64 273 194 167 27 111 179 19 175 125 161 150 276 68 96 0 291 15 237 142 67 120 102 203 22 255 159 94 286 187 84 299 235 76 6 155 83 285 198 310 239 238 192 152 243 16 98 244 241 240 185 25 267 224 47 218 87 118 119 147 182 7 89 69 297 130 208 289 290 24 251 272 205 234 86 307 292 260 117 43 32 202 186 236 210 104 143 92 101 3 245 211 61 73 56 199 257 256 188 149 230 133 132 280 129 263 62 231 261 72 139 258 131 20 105 21 225 93 141 124 8 279 75 303 151 36 137 110 226 181 40 222 271 288 42 170 253 171 283 212 97 168 54 229 270 112 228 18 14 204 206 66 158 144 154 45 33 39 90 209 306 37 284 250 2 201 262 116 177 162 178 38 49 265 298 180 127 82 176 193 28 300 5 282 12 197 301 216 128 115 140 17 293 219 207 183 214 79 220 52 10 264 148 95 103 57 134 213 164 252 107 157 223 77 294 74 48 123 195 31 50 287 275 122 173 59 146 138 9 259 109 11 156 13 63 53 305 108 302 51 249 126 100 71 189 274 233 246 295 163 135 242 "
    cout << "5 309 59 305 36 167 218 173 248 82 45 146 161 107 27 255 216 31 92 228 166 233 222 81 270 79 278 249 279 269 185 191 137 24 197 282 42 115 86 61 2 47 310 201 267 297 312 66 71 114 154 89 192 35 175 56 122 100 30 170 65 274 195 168 28 112 180 20 176 126 162 151 277 69 97 1 292 16 238 143 68 121 103 204 23 256 160 95 287 188 85 300 236 77 7 156 84 286 199 311 240 239 193 153 244 17 99 245 242 241 186 26 268 225 48 219 88 119 120 148 183 8 90 70 298 131 209 290 291 25 252 273 206 235 87 308 293 261 118 44 33 203 187 237 211 105 144 93 102 4 246 212 62 74 57 200 258 257 189 150 231 134 133 281 130 264 63 232 262 73 140 259 132 21 106 22 226 94 142 125 9 280 76 304 152 37 138 111 227 182 41 223 272 289 43 171 254 172 284 213 98 169 55 230 271 113 229 19 15 205 207 67 159 145 155 46 34 40 91 210 307 38 285 251 3 202 263 117 178 163 179 39 50 266 299 181 128 83 177 194 29 301 6 283 13 198 302 217 129 116 141 18 294 220 208 184 215 80 221 53 11 265 149 96 104 58 135 214 165 253 108 158 224 78 295 75 49 124 196 32 51 288 276 123 174 60 147 139 10 260 110 12 157 14 64 54 306 109 303 52 250 127 101 72 190 275 234 247 296 164 136 243" << endl;
}

