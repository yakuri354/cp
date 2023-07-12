#include <iostream>
#include <vector>
#include <map>
#include <valarray>
#include <iomanip>

using namespace std;
using ll = long long;
using ld = long double;

const ld PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620;

void resolve() {
    ll a, b;
    cin >> a >> b;
    if (a > b) {
        swap(a, b);
    }

    cout << fixed << setprecision(39);

    ld l = sqrt(3) / 2;
    ld r = 1;
    for (ll i = 0; i < 1000000; ++i) {
        ld COS = (l + r) / 2;

        ld side = a / COS;
        ld aAngle = acos(COS);
        ld bAngle = PI / 6.0 - aAngle;
        ld cosBAngle = cos(bAngle);
        ld minB = side * cosBAngle;
        if (minB > b) {
            l = COS;
        } else {
            r = COS;
        }
    }

    cout << a / l << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
