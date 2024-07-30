#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<int> basis(32, 0);
int cnt = 0;

void add_to_basis(int mask) {
    for (int i = 30; i >= 0; i--) {
        if ((mask & (1 << i)) == 0)
            continue;
        if (basis[i] == 0) {
            cnt++;
            basis[i] = mask;
        }
        mask ^= basis[i];
    }
}

int get_k(int k) {
    k--;
    int curr = 0, bit = cnt - 1;
    for (int i = 30; i >= 0; i--) {
        if (basis[i] == 0)
            continue;
        if ((1 << bit) & k) {
            if ((curr & (1 << i)) == 0)
                curr ^= basis[i];
        }
        else {
            if (curr & (1 << i))
                curr ^= basis[i];
        }
        bit--;
    }
    return curr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    while (n--) {
        int t, k;
        cin >> t >> k;
        if (t == 1)
            add_to_basis(k);
        else
            cout << get_k(k) << "\n";
    }
}