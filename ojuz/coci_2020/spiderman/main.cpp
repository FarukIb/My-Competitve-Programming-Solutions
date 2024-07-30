#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> mark(1e6 + 1, 0);
    map<int, int> histo;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        histo[x]++;
        arr.push_back(x);
    }

    for (pii x : histo) {
        if (x.first < k || x.first == k)
            continue;
        for (int i = k; i <= 1e6; i += x.first)
            mark[i] += x.second;
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (k == 0)
            cout << mark[arr[i]] - 1 <<" ";
        else
            cout << mark[arr[i]] << " ";
    }

    if (k == 0)
        cout << mark[arr[n - 1]] - 1 << "\n";
    else
        cout << mark[arr[n - 1]] << "\n";
}
