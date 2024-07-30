#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++)
        s[i] = tolower(s[i]);
    
    set<char> vowels;
    vowels.insert('a'); vowels.insert('e'); vowels.insert('i'); vowels.insert('o'); vowels.insert('u');

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = vowels.count(s[i]) ? -1 : 2;
    vector<int> suff_arr(n + 1);

    suff_arr[n] = 0;
    vector<pii> guys;
    guys.push_back({0, n});
    for (int i = n - 1; i >= 0; i--) {
        suff_arr[i] = suff_arr[i + 1] + arr[i];
        if (suff_arr[i] < guys[guys.size() - 1].first)
            guys.push_back({suff_arr[i], i});
    }

    reverse(guys.begin(), guys.end());
    int maxi = 0;
    for (int i = 0; i < n; i++) {
        auto ite = upper_bound(guys.begin(), guys.end(), pii(suff_arr[i], (int)1e9)) - guys.begin() - 1;
        if (ite < 0 || guys[ite].second <= i)
            continue;
        maxi = max(maxi, guys[ite].second - i);
    }

    if (maxi == 0) {
        cout << "No solution\n";
        return 0;
    }

    int sum = 0; int num = 0;
    for (int i = 0; i < maxi; i++)
        sum += arr[i];
    if (sum >= 0)
        num++;
    for (int i = 0; i < n - maxi; i++) {
        sum -= arr[i];
        sum += arr[i + maxi];
        if (sum >= 0)
            num++;
    }

    cout << maxi << " " << num << "\n";
}