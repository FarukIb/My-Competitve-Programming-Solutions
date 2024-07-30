#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> m >> n;
    vector<vector<int> > arr(n, vector<int>(3));
    vector<int> points(m);
    for (int i = 0; i < m; i++)
        cin >> points[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 3; j++)
            cin>> arr[i][j];
    
    ll best = 1e18;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<vector<int> > my;
        ll cost = 0;
        for (int j = 0; j < n; j++) {
            if ((1 << j) & mask)
            {
                cost += arr[j][2];
                my.push_back(arr[j]);
            }
        }

        bool here = true;
        for (int i = 0; i < m; i++) {
            bool contained = false;
            for (int j = 0; j < my.size(); j++) {
                if (my[j][0] <= points[i] and my[j][1] >= points[i])
                {
                    contained = true;
                    break;
                }
            }
            if (!contained)
            {
                here = false;
                break;
            }
        }

        if (here)
            best = min(best, cost);
    }

    if (best == 1e18)
        cout << "-1\n";
    else
        cout << best << "\n";
}