#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int n;
bool check(ld h1, ld h2) {
    ld h = 0;
    for (int i = 2; i < n; i++)
    {
        h = 2 * h2 - h1 + 2;
        if (h < 0)
            return false;
        h1 = h2;
        h2 = h;
    }
    return true;
}

ld out(ld h1, ld h2) {
    ld h = 0;
    ld outt = 1e15;
    for (int i = 2; i < n; i++)
    {
        h = 2 * h2 - h1 + 2;
        h1 = h2;
        h2 = h;
    }
    return h;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ld a;
    while (cin >> n >> a) {
        ld l = 0, r = a;
        while (r - l > 1e-15) {
            ld mid = (r + l) / 2;
            if (check(a, mid))
                r = mid;
            else
                l = mid;
        }
        cout << fixed << setprecision(2) << abs(out(a, l)) << "\n";
    }
}
