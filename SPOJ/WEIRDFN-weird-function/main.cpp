#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double
#define mod (int)1000000007

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        priority_queue<int> smal;
        priority_queue<int> big;
        smal.push(1);

        ll a, b, c;
        int n;
        cin >> a >> b >> c >> n;

        ll sum = 1;
        for (int i = 1; i < n; i++) {
            ll m = smal.top();
            cout << m << "\n";

            m *= a;
            m += b * (i + 1);
            m += c;
            m = m % mod;

            if (m > smal.top())
                big.push(-m);
            else
                smal.push(m);
            
            if (smal.size() - big.size() > 1)
            {
                big.push(-smal.top());
                smal.pop();
            }
            else if (big.size() > smal.size())
            {
                smal.push(-big.top());
                big.pop();
            }


            sum += m;
        }

        cout << sum << "\n";
    }
}
