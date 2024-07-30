#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct prefsum {
    vector<vector<int> > mat;
    prefsum(int n, vector<vector<int> > matt) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != 0)
                    matt[i][j] += matt[i - 1][j];
                if (j != 0)
                    matt[i][j] += matt[i][j - 1];
                if (i != 0 and j != 0)
                    matt[i][j] -= matt[i - 1][j - 1];
            }
        }
        mat = matt;
    }

    int query(int x1, int y1, int x2, int y2){
        int out = mat[x2][y2];
        if (x1 != 0)
            out -= mat[x1 - 1][y2];
        if (y1 != 0)
            out -= mat[x2][y1 - 1];
        if (x1 != 0 and y1 != 0)
            out += mat[x1 - 1][y1 - 1];
        return out;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<vector<int> > mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
            mat[i][j] = s[j] == '*' ? 1 : 0;
    }
    prefsum asd(n, mat);
    while (q--) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        cout << asd.query(x1, y1, x2, y2) << "\n";
    }
}