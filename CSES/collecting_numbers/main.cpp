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
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        int o; cin >> o;
        arr[o - 1] = i;
    }

    int c = 1;
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[i - 1])
            c++;
    cout << c <<"\n";
}