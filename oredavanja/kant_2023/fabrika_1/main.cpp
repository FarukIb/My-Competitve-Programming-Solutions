#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >>n >> m;
    vector<vector<int> > days(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> days[j][i];
    for (int j = 0; j < m; j++)
        cout << *max_element(days[j].begin(), days[j].end()) << " ";
    cout << "\n";
}