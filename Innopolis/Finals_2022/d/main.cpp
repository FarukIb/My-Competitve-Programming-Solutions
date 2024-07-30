#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int myMod(int& x, int base) {
    x %= base;
    if (x < 0)
        x += base;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    
    int sum = a * b - c * d;

    int f = c - a, t = d - b;

    int sumMod = sum; myMod(sumMod, f);

    set<int> mods;
    int x = 1, curr = t; myMod(curr, t);
    if (curr == sumMod) {
        cout << "YES\n";

        cout << (sum - x * t) / f << " " << x << "\n";
        return 0;
    }
    while (mods.find(curr) == mods.end()) {
        mods.insert(curr);
        curr += t;
        x++;
        myMod(curr, f);
        
        if (curr == sumMod) {
            cout << "YES\n";
            cout << (sum - x * t) / f << " " << x << "\n";
            return 0;
        }
    }
    cout << "NO" << "\n";
}
