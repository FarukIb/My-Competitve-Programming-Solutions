#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int k;
    cin >> k;
    string s;
    cin >> s;

    set<char> sett;
    for (int i = 0; i < k; i++)
        sett.insert('a' + i);
    
    for (int i = 0; i < s.size() / 2 + s.size() % 2; i++) {
        char f = s[i], sec = s[s.size() - i - 1];
        if (f == '?' && sec == '?')
            continue;
        
        if (f == '?')
            s[i] = sec;
        else if (sec == '?')
            s[s.size() - i - 1] = f;
        sett.erase(sec);
        sett.erase(f);
    }

    vector<char> left;
    for (char x : sett)
        left.push_back(x);
    sort(left.begin(), left.end());

    for (int i = s.size() / 2 + s.size() % 2 - 1; i >= 0; i--) {
        char f = s[i], sec = s[s.size() - i - 1];
        if (!(f == '?' && sec == '?'))
            continue;
        
        if (left.empty()) {
            s[i] = 'a';
            s[s.size() - i - 1] = 'a';
            continue;   
        }
        s[i] = left[left.size() - 1];
        s[s.size() - i - 1] = s[i];
        sett.erase(s[i]);
        left.pop_back();
    }

    string rev = s;
    reverse(rev.begin(), rev.end());
    if (rev != s || sett.size() != 0)
        cout << "IMPOSSIBLE\n";
    else
        cout << s << "\n";
}
