#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> guys;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
                vector<int> v = {i, j, 0};
                cin >> v[2];
                v[2] -= 1;
                guys.push_back(v);
            }
        }

        vector<int> perm = {0, 1, 2};
        vector<int> shift = {0, 0, 0};
        string s;
        cin >> s;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'R') {
                shift[1] += 1;
                if (shift[1] >= n)
                    shift[1] -= n;
            } else if (s[i] == 'L') {
                shift[1] -= 1;
                if (shift[1] < 0)
                    shift[1] += n;
            } else if (s[i] == 'U') {
                shift[0] -= 1;
                if (shift[0] < 0) 
                    shift[0] += n;
            } else if (s[i] == 'D') {
                shift[0] += 1;
                if (shift[0] >= n) 
                    if (shift[0] >= n)
                        shift[0] -= n;
            } else if (s[i] == 'I') {
                swap(perm[1], perm[2]);
                swap(shift[1], shift[2]);
            } else if (s[i] == 'C') {
                swap(perm[0], perm[2]);
                swap(shift[0], shift[2]);
            }
        }

        vector<vector<int> > out(n, vector<int>(n));
        for (auto guy : guys) {
            vector<int> neww = {guy[perm[0]], guy[perm[1]], guy[perm[2]]};
            for (int i = 0; i < 3; i++)
            {
                neww[i] += shift[i];
                neww[i] %= n;
                if (neww[i] < 0)
                    neww[i] += n;
            }
            out[neww[0]][neww[1]] = neww[2] + 1;
        }

        for (vector<int> a : out) {
            for (int b : a)
                cout << b << " ";
            cout << "\n";
        }
        cout << "\n";
    }
}