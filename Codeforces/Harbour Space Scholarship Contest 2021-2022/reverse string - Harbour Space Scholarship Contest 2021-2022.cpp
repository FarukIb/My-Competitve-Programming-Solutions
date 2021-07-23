#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>

#define pii pair<int, int>
#define ll long long
#define MOD (int)1e9 + 7

using namespace std;

bool possible;
map<pii, bool> memo;
string a, b;

void recur(int chip, int i, bool movedLeft)
{
    if (possible)
        return;
    if (i == b.size())
    {
        possible = true;
        return;
    }
    if (chip < 0 || chip >= a.size())
        return;
    if (a[chip] != b[i])
        return;
    if (memo[pii(chip, i)])
        return;
    memo[pii(chip, i)] = true;
    
    if (!movedLeft)
        recur(chip + 1, i + 1, movedLeft);
    recur(chip - 1, i + 1, true);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--)
    {
        cin >> a >> b;

        possible = false;
        memo.clear();

        for (int i = 0; i < a.size(); i++)
            recur(i, 0, false);

        if (possible)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}
