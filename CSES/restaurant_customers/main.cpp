#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pii> events;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        events.push_back({a, 1});
        events.push_back({b, -1});
    }
    sort(all(events));
    int maxi = 0, c = 0;
    for (pii a : events) 
        c += a.second, maxi = max(maxi, c);
    cout << maxi << "\n";
}