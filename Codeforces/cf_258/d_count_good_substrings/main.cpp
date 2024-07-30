#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    pii As(0, 0), Bs(0, 0);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a')
        {
            if (i % 2 == 0)        
                As.first++;
            else
                As.second++;
        }
        else {
            if (i % 2 == 0)        
                Bs.first++;
            else
                Bs.second++;
        }
    }

    ll odd = 0, even = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') {
            if (i % 2 == 1)
                odd += Bs.first, even += Bs.second, Bs.second--;
            else
                odd += Bs.second, even += Bs.first, Bs.first--;
        }
        else {
            if (i % 2 == 1)
                odd += As.first, even += As.second, As.second--;
            else
                odd += As.second, even += As.first, As.first--;
        }
    }

    // mixed the two up and too lazy to change the code so im changing output
    cout << odd << " " << even << "\n";
}