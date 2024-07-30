#include <bits/stdc++.h>
#define mp make_pair

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> primes;
void make_primes(int n) {
    vector<bool> visited(n + 1, false);
    for (int i = 2; 2 * i <= n; i++) {
        if (visited[i])
            continue;
        if (i > 2)
            primes.push_back(i);
        for (int j = i * 2; j < n; j += i)
            visited[j] = true;
    }
    primes.push_back(2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    make_primes(n);

    vector<pii> out;
    vector<bool> used(n + 1, false);
    for (int x : primes) {
        vector<int> guys;
        for (int i = x; i <= n; i += x) {
            if (used[i])
                continue;
            guys.push_back(i);
            used[i] = true;
        }
        if (guys.size() % 2 == 0) {
            for (int i = 0; i < guys.size(); i += 2)
                out.push_back(mp(guys[i], guys[i + 1]));
        }
        else if (guys.size() > 2){
            vector<int> guys2;
            for (int i : guys)
                if (i != 2 * x)
                    guys2.push_back(i);
            if (2 * x <= n)
                used[2 * x] = false;
            for (int i = 0; i < guys2.size(); i += 2)
                out.push_back(mp(guys2[i], guys2[i + 1]));
        }
    }

    cout << out.size() << "\n";
    for (pii s : out)
        cout << s.first << " " << s.second << "\n";
}