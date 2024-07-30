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
    vector<pair<pii, int>> ran(n);
    set<int> al;
    for (int i = 0; i < n; i++) {
        cin >> ran[i].first.first;
        cin >> ran[i].first.second;
        cin >> ran[i].second;
        al.insert(ran[i].first.first);
        al.insert(ran[i].first.second);
    }
    map<int, int> comp; int cnt = 1;
    for (int a : al)
        comp[a] = cnt++;
    vector<vector<pair<pii, int> > > ran2(cnt);
    for (int i = 0; i < n; i++)
    {
        ran[i].first.first = comp[ran[i].first.first],
         ran[i].first.second = comp[ran[i].first.second];
        ran2[ran[i].first.second].push_back(ran[i]);
    }
    sort(all(ran));

    vector<ll> dp(cnt);
    for (int i = 1; i < cnt; i++) {
        dp[i] = dp[i - 1];
        for (auto &[a, c] : ran2[i]) 
            dp[a.second] = max(dp[a.second], dp[a.first - 1] + c);
    }
    cout << *max_element(all(dp)) << endl;
}