#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()
#define val(o, a) (a.first * mults[o].first + a.second * mults[o].second)
#define dist(a, b) (abs(a.first - b.first) + abs(a.second - b.second))

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<vector<int> > arr(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    
    vector<pii> mults = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    vector<vector<pii> > best_points(k + 1, vector<pii>(4, mp(-1, -1)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int o = 0; o < 4; o++)
            {
                if (best_points[arr[i][j]][o] == mp(-1, -1) || val(o, best_points[arr[i][j]][o]) < val(o, mp(i, j)))
                    best_points[arr[i][j]][o] = mp(i, j);
            }
        }
    }

    vector<int> seq(s);
    for (int i = 0; i < s; i++)
        cin >> seq[i];
    
    vector<vector<int> > dp(s, vector<int>(4, 0));
    for (int i = 1; i < s; i++) {
        for (int j = 0; j < 4; j++) { // j is current
            for (int o = 0; o < 4; o++) { // o is prev
                pii prev_point = best_points[seq[i - 1]][o];
                pii my_point = best_points[seq[i]][j];
                dp[i][j] = max(dp[i][j], max(dp[i - 1][o], dist(prev_point, my_point)));
            }
        }
    }

    cout << *max_element(all(dp[s - 1])) <<"\n";
}