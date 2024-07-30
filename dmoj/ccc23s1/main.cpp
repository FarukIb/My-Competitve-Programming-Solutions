#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    vector<int> mid(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    int sum = 0;

    auto process = [&](vector<int> my) {
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                mid[i] ^= my[i];

            sum += my[i] * (i % 2);
            
            if (my[i] == 1 and (i == 0 || my[i - 1] == 0))
                sum += 2;
        }
    };
    process(a);
    process(b);

    cout << sum + count(all(mid), 1) << "\n";
}