#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int A, B, C;
    cin >> A >> B;
    C = A + B;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        A = __gcd(abs(a), A);
        B = __gcd(abs(b), B);
        C = __gcd(abs(a + b), C);
    }

    cout << A * C / __gcd(A, C) << " 0\n";
    cout << "0 " << C * B / __gcd(B, C) << "\n";
}
