#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        if (n == 2)
        {
            cout << "TAK\n";
            continue;
        }
        else if (n == 3) {
            if (arr[0] == arr[1] and arr[1] == arr[2])
                cout << "NIE\n";
            else
                cout << "TAK\n";
            continue;
        }

        vector<int> type(n, -1);
        int cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            if (type[i] != -1)
                continue;
            for (int j = 0; j < n - 1; j++) {
                if (arr[i] == arr[j] and arr[i + 1] == arr[j + 1])
                    type[j] = cnt;
            }
            cnt++;
        }

        if (type[0] == type[n - 2])
        {
            cout << "NIE\n";
            continue;
        }

        int num = 0;
        for (int i = 1; i < n - 1; i += 2)
            num++;
        
        bool possible = false; 
        for (int mask = 0; mask < (1 << num) and !possible; mask++) {
            bool good = true;
            vector<bool> here(n);
            vector<bool> painted(n);
            here[type[0]] = here[type[n - 2]] = true;
            for (int b = 0; b < num and good; b++) {
                if (((1 << b) & mask) != 0) {
                    painted[1 + b* 2] = true, painted[1 + b * 2 + 1] = true;
                    if (here[type[1 + b * 2]] == true)
                        good = false;
                    else
                        here[type[1 + b * 2]] = true;
                }
            }
            painted[n - 1] = painted[n - 2] = true;
            for (int i = 2; i < n - 1 and good; i += 2) {
                if (!painted[i] || !painted[i + 1]) {
                    if (here[type[i]] == true)
                        good = false;
                    else
                        here[type[i]] = true;
                }
            }
            if (good)
                possible = true;
        }
        if (possible)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}