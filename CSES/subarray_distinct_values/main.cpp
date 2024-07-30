#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    ll out = 0;
    map<int, int> cnt; int num_larg = 0, r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n && num_larg + (int)(cnt[arr[r]] == 0) <= k) {
            cnt[arr[r]]++;
            if (cnt[arr[r]] == 1)
                num_larg++;
            r++;
        }
        out += r - l;

        cnt[arr[l]]--;
        if (cnt[arr[l]] == 0)
            num_larg--;
    }

    cout << out << endl;
}