#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N; ll M;
    cin >> N >> M;
    int n = N / 2, m = N - n;
    vector<ll> s1(n), s2(m);
    for (int i = 0; i < n; i++)
        cin >> s1[i];
    for (int j = 0; j < m; j++)
        cin >>s2[j];
    
    vector<ll> all_sums;
    for (int i = 0; i < (1 << n); i++) {
        ll s = 0;
        for (int j = 0; j < n; j++)
            if ((i & (1 << j)) != 0)
                s += s1[j];
        all_sums.push_back(s);
    }
    sort(all(all_sums));
    ll out = 0;
    for (int i = 0; i < (1 << m); i++) {
        ll s = 0;
        for (int j = 0; j < m; j++)
            if ((i & (1 << j)) != 0)
                s += s2[j];
        out += upper_bound(all(all_sums), M - s) - all_sums.begin();
    }

    cout << out << "\n";
}