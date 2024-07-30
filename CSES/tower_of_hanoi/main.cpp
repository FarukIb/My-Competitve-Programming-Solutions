#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void recur(int n, int f, int t, int h, vector<pair<int, int> >& arr) {
    if (n == 0)
        return;
    recur(n - 1, f, h, t, arr);
    arr.push_back(pair<int, int>(f, t));
    recur(n - 1, h, t, f, arr);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pii> out;
    recur(n, 1, 3, 2, out);
    cout << out.size() << endl;
    for (auto p : out)
        cout << p.first << " " << p.second << endl;
}