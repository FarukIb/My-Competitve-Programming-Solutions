#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >>s;
    vector<int> cnt(30);
    for (int i = 0; i < s.size(); i++)
        cnt[s[i] - 'A']++;
    
    int nep = -1; bool ok = true;
    for (int i = 0; i <= 'Z' - 'A'; i++)
    {
        if (cnt[i] % 2 and nep == -1)
            nep = i;
        else if (cnt[i] % 2)
            ok = false;
    }
    if (!ok)
        cout << "NO SOLUTION" << endl;
    else {
        string o;
        for (int i = 0; i <= 'Z' - 'A'; i++)
            for (int j = 0; j < cnt[i] / 2; j++)
                o += i + 'A';
        string orev = o; reverse(all(orev));
        if (nep != -1)
            o += 'A' + nep;
        cout << o + orev << endl;
    }
}