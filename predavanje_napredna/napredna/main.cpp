#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e6 + 10;
vector<int> primes;
void make_sito() {
    vector<bool> sito(maxn, false);
    // sito[i] == false, i - prost
    for (int i = 2; i * i < maxn; i++) {
        if (sito[i])
            continue;
        for (int j = i * i; j < maxn; j += i)
            sito[j] = true;
    }

    for (int i = 2; i < maxn; i++)
        primes.push_back(i);

    // O(n*log(log(n)))
    // 1/1 + 1 /2 + 1 /3 + 1 / 4 ?= log n
}

/* ZA SVAKI PROSTI BROJ

p

2*p, 3*p, 4*p, 5*p,. ....
    sito[taj broj] = true;

*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    make_sito();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >>n;

        vector<int> facts;
        for (int i = 0; i <n; i++){
            int s;
            cin >> s;
            for (int p : primes) {
                if (p > s)
                    break;
                if (s % p == 0)
                    facts.push_back(p);
                while (s % p == 0)
                    s /= p;
            }
            if (s > 1)
                facts.push_back(s);
        }

        sort(facts.begin(), facts.end());
        bool ok = false;
        for (int i = 1; i < facts.size(); i++) {
            if (facts[i] == facts[i - 1])
                ok = true;
        }

        if (ok)
            cout <<"YES\n";
        else
            cout << "NO\n";
    }
}