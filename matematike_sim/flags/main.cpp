#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool check(string s) {
    int maxi = 0, c = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'b')
            c++;
        else
            c = 0;
        maxi = max(maxi, c);
    }
    return maxi >= 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s = "bbbbbrrryy";
    set<string> checked; int num = 0;
    do {
        if (checked.count(s))
            continue;
        checked.insert(s);
        if (check(s))
            num++;
    } while (next_permutation(all(s)));

    cout << num << endl;
}