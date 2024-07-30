#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void ispis(vector<string> out, int n, int m, int r, int c, bool flipped) {
    // count rows
    int R = 0;
    for (int i = 0; i < n; i++) {
        bool ok = true;
        for (int j = 0; j < m; j++)
            if (out[i][j] != out[i][m - j - 1])
                ok = false;
        if (ok)
            R++;
    }
    // count collumns
    int C = 0;
    for (int i = 0; i < m; i++)
    {
        bool ok = true;
        for (int j = 0; j < n; j++) 
            if (out[j][i] != out[n - j - 1][i])
                ok = false;
        if (ok)
            C++;
    }

    if (r != R || c != C)
        cout << "IMPOSSIBLE\n";
    else {
        if (!flipped) {
            for (string s : out)
                cout << s << "\n";
        }
        else {
            for (int j = 0; j < m; j++) {
                for (int i = 0; i < n; i++)
                    cout << out[i][j];
                cout << "\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, r, c;

    cin >> n >> m >> r >> c;

    bool flipped = false;
    if (r == 0 and c == 0) {
        vector<string> out(n, string(m, 'b'));
        for (int i = 0; i < n; i++)
            out[i][0] = 'a';
        for (int i = 0; i < m; i++)
            out[0][i] = 'a';
        out[0][0] = 'c';
        
        ispis(out, n, m, r, c, flipped);
    }
    else if (r == n and c == m) {
        vector<string> out(n, string(m, 'b')); 
        ispis(out, n, m, r, c, flipped);
    }
    else if (r > 0 and r < n and c > 0 and c < m) {
        vector<string> out(n, string(m, 'b'));
        for (int i = 0; i < r; i++)
            for (int j = 0; j < m; j++)
                out[i][j] = 'a';
        
        for (int i = 0; i < c; i++)
            for (int j = 0; j < n; j++)
                out[j][i] = 'a';
        ispis(out, n, m, r, c, flipped);
    } else {

        if (c == 0 || c == m)
            flipped = true, swap(n, m), swap(r, c);
        vector<string> out(n, string(m, 'a'));
        if (r == 0) {
            for (int i = 0; i < n; i++)
                out[i][0] = 'b';
            for (int i = 0; i < m - c; i++)
                out[0][i]++;
        } else {
            int ogc = c;
            c = m - c;
            for (int i = 0; i < m; i++) {
                if (c <= 1)
                    break;
                out[0][i] = 'b', out[0][m - i - 1] = 'b';
                c -= 2;
            }
            if (c == 1 and m % 2)
                out[0][m / 2] = 'b';
            
            c = ogc;
        }

        ispis(out, n, m, r, c, flipped);
    }
}