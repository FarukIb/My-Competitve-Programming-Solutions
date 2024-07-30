#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pii> tracks(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> tracks[i].first >> tracks[i].second;
    while (q--) {
        pii l, r;
        cin >> l.first >> l.second;
        cin >> r.first >> r.second;
        if (l.second > r.second) {
            swap(l, r);
        }

        ll dist = 0;
        for (int tr = l.second + 1; tr <= r.second; tr++) {
            l.second++;

            if (l.first < tracks[tr].first)
                dist += tracks[tr].first - l.first, l.first = tracks[tr].first;
            else if (l.first > tracks[tr].second)
                dist += -tracks[tr].second + l.first, l.first = tracks[tr].second;
            dist++;
        }

        dist += abs(l.first - r.first);

        cout << dist << "\n";
    }
}
