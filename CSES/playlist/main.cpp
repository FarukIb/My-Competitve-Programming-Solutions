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
    vector<int>arr(n);
    for (int i = 0; i < n; i++)
        cin >>arr[i];
    map<int, int> histo; int num2 = 0, r = 1; int out = 0, last_good = 0;
    histo[arr[0]] = 1;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            histo[arr[i - 1]]--;
            if (histo[arr[i - 1]] == 1)
                num2--;
        }
        while (r < n && num2 == 0) {
            histo[arr[r]]++;
            if (histo[arr[r]] == 2)
                num2++;
            else
                last_good = r;
            r++;
        }
        out = max(out, last_good - i + 1);
    }

    cout << out << "\n";
}