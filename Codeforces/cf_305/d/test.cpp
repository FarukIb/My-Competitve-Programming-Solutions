#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> og  = arr;
    sort(arr.begin(), arr.end());

    map<int, int> mapp;
    int l = 2;
    mapp[arr[0]] = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1])   
            continue;
        mapp[arr[i]] = l++;
    }

    for (int i = 0; i < n; i++)
        cout << mapp[og[i]] << " ";
    cout << endl;

    while (1) {
        int x;
        cin >> x;
        cout << mapp[x] << endl;
    }
}
