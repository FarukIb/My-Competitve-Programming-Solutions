#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};

    int k;
    cin >> k;
    int lim = k * k * 2;
    vector<bool> marked(lim + 1, false);
    marked[1] = true;

    int siz = 0;
    for (int p : primes) {
        for (int i = 1; i <= lim; i++) {
            if (i * p > lim)
                break;
            if (marked[i]) {
                marked[i * p] = true;
                siz++;
            }
        }
        if (siz >= k)
            break;
    }

    int puted = 0;
    for (int i = lim; i > 0 && puted < k; i--) {
        if (marked[i]) {
            puted++;
            cout << i <<" ";
        }
    }
    cout << "\n";
}