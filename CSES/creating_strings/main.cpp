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
    cin >> s; sort(all(s));
    set<string> sett;
    do {
        sett.insert(s);
    } while (next_permutation(all(s)));
    cout << sett.size() << "\n";
    for (auto o : sett)
        cout << o << "\n";
}