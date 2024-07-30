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
    if (n == 1) {
        cout << "1" << endl;
        return 0;
    } else if (n == 2 || n == 3) {
        cout << "NO SOLUTION" <<endl;
        return 0;
    }
    vector<int> base = {2, 4, 1, 3};
    vector<int> f, s;
    for (int i = 5; i <= n; i += 2)
        f.push_back(i);
    for (int i = 6; i <= n; i += 2)
        base.push_back(i);
    f.insert(f.end(), all(base));
    for (int a : f)
        cout << a << " ";
    cout << endl;
}