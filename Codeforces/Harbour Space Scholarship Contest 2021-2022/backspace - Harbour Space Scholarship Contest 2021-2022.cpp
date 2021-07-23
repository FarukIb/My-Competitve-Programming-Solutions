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

string a, b;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--)
    {
        cin >> a >> b;

        bool ok = false;

        int j = a.size() - 1;
        for (int i = b.size() - 1; i >= 0; i--)
        {
            while (j >= 0 && a[j] != b[i])
                j -= 2;

            if (j < 0)
                break;

            if (i == 0)
                ok = true;
            j--;
        }

        if (ok)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}
