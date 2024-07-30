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
    vector<int> perm = {n, 0, n};
    for (int i = 1; i < n; i++) {
        vector<bool> bad(n+1);
        int treshold = i / 2;
        if (i % 2 == 0)
            treshold--;
        for (int j = 0; j < i; j++) {
            int a;
            cin >> a;
            if (j > treshold)
                bad[a] = true;
        }
        for (int j = 1; j <= i + 1; j++) {
            if (!bad[perm[j-1]] and !bad[perm[j]]) {
                perm.insert(perm.begin()+j, i);
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << perm[i] << " ";
    cout << "\n";
}