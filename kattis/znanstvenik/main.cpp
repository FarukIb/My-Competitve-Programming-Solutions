#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool checkk(vector<string> &mat, int num) {
    set<string> strings;
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < m; i++) {
        string curr = "";
        for (int j = n - 1; j >= num; j--)
            curr += mat[j][i];
        if (strings.count(curr))
            return false;
        strings.insert(curr);
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int R, C;
    cin >> R >> C;
    vector<string> mat(R);
    for (int i = 0; i < R; i++)
        cin >> mat[i];
    
    // brojim koliko redova mogu izbrisati
    int l = 0, r = R, ans = -1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (checkk(mat, mid))
            l = mid + 1, ans = mid;
        else
            r = mid;
    }

    cout << ans << "\n";
}