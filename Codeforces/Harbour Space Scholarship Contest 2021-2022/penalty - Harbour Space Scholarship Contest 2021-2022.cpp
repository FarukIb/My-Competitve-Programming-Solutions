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

int mostPossible, roundsLeft;

bool isOver(int &firstG, int &secondG, int round)
{
    // checking if first can win

    mostPossible = 0, roundsLeft = 10 - round;
    mostPossible += roundsLeft / 2;

    if (firstG + mostPossible < secondG)
        return true;

    // checking if second can win
    mostPossible = 0, roundsLeft = 10 - round;
    mostPossible += roundsLeft / 2;
    if (round % 2 == 1)
        mostPossible++;

    if (secondG + mostPossible < firstG)
        return true;
    
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q, numUndecided;
    char ss;
    int f, s, passed, i, mask;
    cin >> q;
    while (q--)
    {
        string x;
        cin >> x;
        numUndecided = 0;
        for (char ss : x)
            if (ss == '?')
                numUndecided++;

        int mini = 10;
        for (mask = 0; mask < (1 << numUndecided); mask++)
        {
            passed = 0, f = 0, s = 0;
            for (i = 0; i < 10; i++)
            {
                if (i % 2 == 0)
                {
                    if (x[i] == '1')
                        f++;
                    if (x[i] == '?')
                    {
                        if (mask & (1 << passed))
                            f++;
                        passed++;
                    }
                }
                else
                {
                    if (x[i] == '1')
                        s++;
                    if (x[i] == '?')
                    {
                        if (mask & (1 << passed))
                            s++;
                        passed++;
                    }
                }
                if (isOver(f, s, i + 1))
                    mini = min(mini, i + 1);
            }
        }
        cout << mini << endl;
    }
}
