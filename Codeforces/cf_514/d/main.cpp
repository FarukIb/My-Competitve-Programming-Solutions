#include <bits/stdc++.h>
#define pii pair<ld, ld>
#define ll long long
#define ld long double

using namespace std;

vector<pii> points;
int n;

bool possible(ld r) {
    pii curr(-1e18, 1e18);
    for (int i = 0; i < n; i++) {
        ld y = points[i].second, x = points[i].first;
        if (y < 0)
            y = -y;
        if (2*y*r-y*y < 0)
            return false;
        ld cb = sqrt(2*y*r-y*y);

        curr.first = max(x - cb, curr.first);
        curr.second = min(x + cb, curr.second);
    }
    return curr.first < curr.second;
}

ld bin_search() {
    ld l = 0, r = 2e14;

    for (int i = 0; i <= 1000; i++) {
        ld mid = (l + r) / 2.0;
        if (possible(mid)) 
            r = mid;
        else
            l = mid;
    }

    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    points.resize(n);
    int numpos = 0, numneg = 0;
    for (int i = 0; i < n; i++) {
        cin >> points[i].first;
        cin >> points[i].second;

        if (points[i].second < 0)
            numneg++;
        else if (points[i].second > 0)
            numpos++;
    }

    if (numneg > 0 && numpos > 0)
    {
        cout << "-1\n";
        return 0;
    }

    cout << fixed << setprecision(15) << bin_search() << "\n";
}
