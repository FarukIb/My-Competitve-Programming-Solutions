#include <bits/stdc++.h>

using namespace std;

int winner[1000001];
vector<int> moves;
int n, m;

int solve(int curr) {
    if (winner[curr] != -1)
        return winner[curr];

    for (int i = 0; i < m; i++) {
        if (curr + moves[i] <= n) {
            if (solve(curr + moves[i]))
                return winner[curr] = 0;
        }
    }

    return winner[curr] = 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    while (cin >> n >> m) {

        memset(winner, -1, sizeof(winner));
        moves.resize(m, 0);
        for (int i = 0; i < m; i++)
            cin >> moves[i];
        
        if (solve(0))
            cout << "Ollie wins\n";
        else
            cout << "Stan wins\n";
    }
}