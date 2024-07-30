#include <bits/stdc++.h>
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<ld> zeros;
    for (int i = 0; i < n; i++) {
        ld b, k;
        cin >> k >> b;
        if (k == 0)
            continue;
        zeros.push_back(-b / k);
    }

    if (zeros.size() == 0)    
    {
        cout << 0 << "\n";
        return 0;
    }

    sort(zeros.begin(), zeros.end());
    int out = 1;
    for (int i = 1; i < zeros.size(); i++) {
        if (zeros[i] != zeros[i - 1])
            out++;
    }

    cout << out << "\n";
}