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
    set<int> arr;
    for (int i = 0; i < n; i++) {
        int o;
        cin >> o;
        arr.insert(o);
    }
    cout << arr.size() << endl;
}