#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> out = {0};
    for (int p = 0; p < n; p++) {
        for (int i = out.size() - 1; i >= 0; i--)
            out.push_back(out[i] + (1 << p));
    }
    for (int a : out)
        cout << (bitset<32>(a).to_string()).substr(32 - n, n) << endl;
}