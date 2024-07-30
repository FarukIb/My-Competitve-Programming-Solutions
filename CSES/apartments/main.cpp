#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;   
    vector<int> apart(m), apli(n);
    for (int i = 0; i < n; i++)
        cin >>apli[i];
    for (int j = 0; j < m; j++)
        cin >>apart[j];
    sort(all(apart));
    apart.push_back(2e9);
    sort(all(apli));
    int p1 = 0, p2 = 0, cnt = 0;
    for (; p1 < n; p1++) {
        while (apart[p2] < apli[p1] - k)
            p2++;
        if (abs(apli[p1] - apart[p2]) <= k)
            cnt++, p2++;
    }
    cout <<cnt << endl;
}