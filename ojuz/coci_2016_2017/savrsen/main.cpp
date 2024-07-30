#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int b, a;
    cin >> a >> b;

    vector<int> sito(b + 1, 0);
    sito[1] = 1;

    for (int i = 2; i <= b; i++) {
        if (sito[i] != 0)
            continue;
        sito[i] = i + 1;
        for (int j = i * 2; j <= b; j += i) {
            int t = 0;
            int s = j;
            while (s % i == 0)
                s /= i, t++;
            
            if (sito[j / i] == 0 || sito[s] == 0)
                continue;
            sito[j] = sito[j / i] + sito[s] * (j / s);
        }
    }

    ll out = 0;
    for (int i = a; i <= b; i++) 
        out += abs(i - (sito[i] - i));
    cout << out << "\n";
}
