#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;

    int maxi = 1, curr = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != s[i - 1])
            maxi = max(maxi, curr), curr = 0;
        curr++;
    }
    maxi = max(maxi, curr);
    cout << maxi << endl;
}