#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int get_min(multiset<int> &sett, int offset) {
    auto ite = sett.lower_bound(-offset);
    vector<int> guy;
    if (ite != sett.end())
        guy.push_back(abs(*ite + offset));
    if (ite != sett.begin())
        guy.push_back(abs(*prev(ite) + offset));
    return *min_element(all(guy));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n); vector<int> b(n);
    vector<int> inv(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i]--;
        inv[a[i]] = i;
    }
    multiset<int> diffs;
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        b[i]--;
        diffs.insert(inv[b[i]] - i);
    }
    
    int offset = 0;
    for (int i = 0; i < n; i++) {
        cout << get_min(diffs, offset) << "\n";
        int f_diff = inv[b[i]] - i;
        int n_diff = inv[b[i]] - (n - 1);
        diffs.erase(diffs.find(f_diff));
        offset++;
        diffs.insert(n_diff - offset);
    }
}