#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        bool found = false;
        for (int i = 0; i < s.size() - 1; i++)
            if (s[i] == 'i' and s[i + 1] == 't')
                found = true;
        if (found)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    
}