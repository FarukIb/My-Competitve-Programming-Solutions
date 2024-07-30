#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int mod = 26;

int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> n >> q;

    string A, B;
    cin >> A >> B;
    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; i++)
        a[i] = A[i] - 'a', b[i] = B[i] - 'a';
    int b_val = 0, a_val = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2)
            b_val -= mod - b[i];
        else    
            b_val += mod - b[i];
        b_val %= mod;
        if (b_val < 0)
            b_val += mod;
    }
    for (int i = 0; i < n; i++) {
        if (i % 2)
            a_val -= mod - a[i];
        else    
            a_val += mod - a[i];
        a_val %= mod;
        if (a_val < 0)
            a_val += mod;
    }
    
    if (a_val == b_val)
        cout << "da\n";
    else
        cout <<"ne\n";
    while (q--) {
        int x; char y;
        cin >> x >> y;
        x--;

        if (x % 2) 
            a_val += mod - a[x];
        else
            a_val -= mod - a[x];
        a[x] = (y - 'a');
        if (x % 2) 
            a_val -= mod - a[x];
        else
            a_val += mod - a[x];
        a_val %= mod;
        if (a_val < 0)
            a_val += mod;

        if (a_val == b_val)
            cout << "da\n";
        else
            cout << "ne\n";
    }
}