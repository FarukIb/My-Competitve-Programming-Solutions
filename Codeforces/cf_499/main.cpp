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

    int g;
    cin >> g;
    for (int i = 1; i < n; i++)   
    {
        int s;
        cin >> s;
        g = __gcd(g, s);
    }
    g %= k;

    vector<bool> arr(k, 0);
    int s = g, siz = 0;
    while (arr[g] == false) {
        arr[g] = true;
        g += s;
        g %= k;
        siz++;
    }

    cout << siz << "\n";
    for (int i = 0; i < k; i++)
        if (arr[i])
            cout << i << " ";
    cout << "\n";
}
