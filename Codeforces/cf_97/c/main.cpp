#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int m, v; int n;
string get(string curr) {
    int b0 = count(curr.begin(), curr.end(), '0'), b1 = count(curr.begin(), curr.end(), '1');
    if (b1 <= m)
        return "00";
    if (b0 <= v)
        return "11";
    vector<bool> removed(curr.size());
    for (int i = 0; i < curr.size() && m > 0; i++) {
        if (curr[i] == '1')
        {
            m--;
            removed[i] = true;
        }
    }
    for (int i = 0; i < n and v > 0; i++) {
        if (curr[i] == '0') {
            removed[i] = true;
            v--;
        }
    }
    string neww = "";
    for (int i = 0; i < curr.size(); i++) {
        if (!removed[i])
            neww += curr[i];
    }
    m = (n - 2) / 2 + n % 2;
    v = (n - 2) / 2;
    return neww;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    vector<int> uptinici;
    cin >> s;
    n = s.size();
    m = (n - 2) / 2 + n % 2;
    v = (n - 2) / 2;
    for (int i = 0; i < n; i++)
        if (s[i] == '?')
            uptinici.push_back(i);
    
    string all_one = s, all_zero = s;
    for (int i : uptinici)
        all_one[i] = '1', all_zero[i] = '0';
    set<string> possible;
    possible.insert(get(all_one));
    possible.insert(get(all_zero));

    int num_ones = count(all_one.begin(), all_one.end(), '1');
    int num_zero = n - num_ones;
    for (int i : uptinici) {
        all_one[i] = '0';
        num_ones--;
        num_zero++;
        if (num_ones == m+1 and num_zero == v+1)
            possible.insert(get(all_one));
    }
    for (int i : uptinici) {
        all_one[i] = '1';
        num_ones++;
        num_zero--;
        if (num_ones == m+1 and num_zero == v+1)
            possible.insert(get(all_one));
    }
    
    for (string s : possible)
        cout << s << "\n";
}