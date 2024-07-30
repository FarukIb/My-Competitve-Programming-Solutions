#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > edges = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {0, 4},
    {3, 5},
    {2, 6},
    {1, 7},
    {4, 5},
    {4, 7},
    {7, 6},
    {6, 5}
};

const ll mod = 998244353;
const int max_int = 'f';

int get_idx(const int &a, const int &b) {
    int A = a - 'a', B = b - 'a';
    return A + B*(max_int + 1 - 'a');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<set<string> > strings(11);
    int n;
    cin >>n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        string s2 = s;
        reverse(s2.begin(), s2.end());
        strings[s.size()].insert(s);
        strings[s.size()].insert(s2);
    }

    vector<vector<ll> > num_guys(11, vector<ll>(get_idx(max_int, max_int) + 1, 0));
    for (int i = 3; i <= 10; i++) {
        for (string s : strings[i])
            num_guys[i][get_idx(s[0], s[s.size() - 1])]++;
    }

    ll out = 0;
    for (int l0 = 'a'; l0 <= max_int; l0++) {
    for (int l1 = 'a'; l1 <= max_int; l1++) {
    for (int l2 = 'a'; l2 <= max_int; l2++) {
    for (int l3 = 'a'; l3 <= max_int; l3++) {
    for (int l4 = 'a'; l4 <= max_int; l4++) {
    for (int l5 = 'a'; l5 <= max_int; l5++) {
    for (int l6 = 'a'; l6 <= max_int; l6++) {
    for (int l7 = 'a'; l7 <= max_int; l7++) {
        vector<int> letters = {l0, l1, l2, l3, l4, l5, l6, l7};
        
        for (int i = 3; i <= 10; i++) {
            ll curr = 1;
            for (int j = 0; j < 12; j++) {
                int idx = letters[edges[j][0]] - 'a' + (letters[edges[j][1]] - 'a') * (max_int + 1 - 'a');
                curr *= num_guys[i][idx];
                curr %= mod;
            }
            out += curr;
            out %= mod;
        }
    }
    }
    }
    }
    }
    }
    }
    }

    cout << out << "\n";
}