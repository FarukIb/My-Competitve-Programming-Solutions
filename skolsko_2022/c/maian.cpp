#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ld phi = (1 + sqrt(5)) / 2;

    int n;
    cin >> n;
    int min_idx; ld mini = 1e9;
    for (int i = 0; i < n; i++) {
        ld a, b;
        cin >> a >>b;
        ld rat = b / a;
        if (abs(rat - phi) < mini)
            min_idx = i, mini = abs(rat - phi);
        swap(b, a);
        rat = b / a;
        if (abs(rat - phi) < mini)
            min_idx = i, mini = abs(rat - phi);
    }

    cout << min_idx << "\n";
}