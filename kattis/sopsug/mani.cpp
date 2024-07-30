#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<set<int> > cant(n);
    for (int i = 0; i < k; i++)  {
        int a, b;
        cin >> a>> b;
        cant[a].insert(b);
    }
    if (n == 2 and k == 2) {
        cout << "NO\n";
        return 0;
    }
    vector<int> perm;
    for (int tr = 0; tr < 1e7 / n; tr++)
    {
        perm = vector<int>(n);
        for (int i = 0; i < n; i++)
            perm[i] = i;
        
        random_shuffle(all(perm));
        bool ok = true;
        for (int i = 0; i <n - 1; i++)
        {
            if (cant[perm[i]].count(perm[i+1]))
            {
                ok = false;
                break;
            }
        }
        if (ok)
            break;
    }

    if (perm.empty()) {
        cout << "NO\n";
    } else {
        for (int i = 0; i < n - 1; i++)
            cout << perm[i] << " " << perm[i + 1] << "\n";
    }
    
}