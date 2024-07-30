#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    set<int> arr;
    for (int i = 0; i < n; i++)
    {
        int s;
        cin >> s;
        arr.insert(s);
    }
    int a, b;
    cin >> a >>b; int out = 0;
    while (a > b) {
        int mini = a - 1;
        vector<int> to_rem;
        for (int s : arr) {
            int new_val = a - a % s;
            if (new_val < b)
            {
                to_rem.push_back(s);
                continue;
            }
            mini = min(mini, new_val);
        }
        for (int s : to_rem)
            arr.erase(s);
        a = mini;
        out++;
    }
    cout << out << "\n";
}