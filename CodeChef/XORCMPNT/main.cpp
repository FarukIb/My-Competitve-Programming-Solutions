#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void add_to_basis(int mask, vector<int> &basis, int &siz) {
    for (int d = 0; d < 32; d++) {
        if ((mask & (1 << d)) == 0)
            continue;
        if (basis[d] == 0) {
            basis[d] = mask;
            siz++;
            break;
        }
        mask ^= basis[d];
    }
}

int basis_size(vector<int> arr) {
    vector<int> basis(32, 0);
    int out = 0;
    for (int s : arr) 
        add_to_basis(s, basis, out);
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int k, m;
        cin >> k >> m;
        vector<int> arr(m);
        for (int i = 0; i < m; i++)
            cin >> arr[i];
        
        cout << (1 << k) / (1 << (basis_size(arr))) << "\n";
    }
    
}