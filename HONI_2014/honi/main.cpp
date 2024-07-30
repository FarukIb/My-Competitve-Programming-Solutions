#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int max_b = 652;

int mapp[max_b][max_b];

int cum_sum[max_b][max_b];
void init() {
    for (int i = 0; i < max_b; i++) {
        for (int j = 0; j < max_b; j++) {
            if (i == 0 and j == 0)
                continue;
            if (j > 0)
                cum_sum[i][j] += cum_sum[i][j - 1];
            if (i > 0)
                cum_sum[i][j] += cum_sum[i - 1][j];
            if (i > 0 && j > 0)
                cum_sum[i][j] -= cum_sum[i - 1][j - 1];
        }
    }
}

int get_sum(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2)
        return 0;

    int out = cum_sum[x2][y2];
    if (y1 != 0)
        out -= cum_sum[x2][y1 - 1];
    if (x1 != 0)
        out -= cum_sum[x1 - 1][y2];
    if (x1 != 0 && y1 != 0)
        out += cum_sum[x1 - 1][y1 - 1];
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pii> arr(n);
    vector<vector<pii> > first_vals(max_b);
    for (int i = 0; i < n; i++) {
        pii a;
        cin >> a.first >> a.second;
        mapp[a.first][a.second]++;
        cum_sum[a.first][a.second]++;
        first_vals[a.first].push_back({a.second, i});
        arr[i] = a;
    }
    init();

    for (pii s : arr) {
        int best = 1;
        best += get_sum(s.first + 1, s.second + 1, max_b - 1, max_b - 1);

        int worst = n;
        worst -= get_sum(0, 0, s.first - 1, s.second - 1);

        if (s.second == 650)
            worst -= mapp[s.first][0];
        if (s.first == 650)
            worst -= mapp[0][s.second];
        cout << best << " " << worst << "\n";
    }
}