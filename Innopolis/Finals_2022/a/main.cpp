#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, b, w;
        cin >> n >> m >> b >> w;
        n *= 4, m *= 4;
        
        string trash = "";
        for (int i = 0; i < m; i++)
            trash += '.';
        vector<string> out(n, trash);

        queue<pii> whites;
        whites.push(pii(1, 0));
        for (int i = 1; i <= m - 3 && b > 0; i += 2) {
            b--, w--;
            out[1][i] = 'B';
            out[1][i - 1] = 'W';
            whites.push(pii(0, i));
            whites.push(pii(1, i + 1));
            whites.push(pii(2, i));
            
            if (i % 4 == 1) {
                for (int j = 3; j <= n - 3 && b > 0; j += 2) {
                    out[j - 1][i] = 'W';
                    out[j][i] = 'B';
                    b--, w--;

                    whites.push(pii(j + 1, i));
                    whites.push(pii(j, i + 1));
                    whites.push(pii(j, i - 1));
                }
            }
        }

        while (w > 0) {
            pii curr = whites.front();
            whites.pop();

            if (out[curr.first][curr.second] != '.')
                continue;
            w--;
            out[curr.first][curr.second] = 'W';
        }

        for (int i = 0; i < n; i++)
            cout << out[i] << "\n";
    }
}