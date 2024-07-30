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
    for (int b = 1;; b *= 2) {
        vector<int> guys;
        for (int i = 1; i <= n; i++)
            if (i & b)
                guys.push_back(i);
        if (guys.empty())
            break;
        random_shuffle(all(guys));
        cout << b << ":";
        for (int i : guys)
            cout << " " << i;
        cout << endl;
    }
}