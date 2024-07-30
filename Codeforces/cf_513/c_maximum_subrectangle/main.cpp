#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
    int n, m, x;
    cin >> n >> m;

    vector<ll> a(n + 1, 0);
    vector<ll> b(m + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> a[i + 1];
        a[i + 1] += a[i]; 
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i + 1];
        b[i + 1] += b[i]; 
    }
    cin >> x;

    vector<ll> A(n + 1, (ll)1e18); A[0] = 0;
    vector<ll> B(m + 1, (ll)1e18); B[0] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            A[j - i] = min(A[j - i], a[j] - a[i]);
    for (int i = 0; i <= m; i++)
        for (int j = i + 1; j <= m; j++)
            B[j - i] = min(B[j - i], b[j] - b[i]);
    
    int out = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i] * B[j] <= x)
                out = max(out, i * j);
        }
    }

    cout << out << "\n";
}