#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll cumSum[(ll)2e6];

int main() {
    for (ll i = 0; i <= (ll)1e6; i++) {
        if (i % 4 != 2)
            cumSum[i]++;
        cumSum[i] += cumSum[i - 1];
    }
    

    string line;
    while (getline(cin, line)) {
        ll a, b;
        string first, second;
        bool hasSpace = false;
        for (ll i = 0; i < line.size(); i++) {
            if (line[i] == ' ')
                hasSpace = true;
            else if (!hasSpace)
                first += line[i];
            else
                second += line[i];
        }

        a = stoll(first);
        if (hasSpace) {
            b = stoll(second);

            ll sum = cumSum[b];
            if (a != 0)
                sum -= cumSum[a - 1];
            
            cout << sum << endl;
        }
        else {
            bool small = false;
            if (a < 0)
                a = abs(a), small = true;

            if (a % 4 == 0) {
                ll A = a / 4 + 1, B = a / 2 - A;

                if (small)
                    swap(A, B);
                cout << A << " " << B << "\n";
            }
            else if (a % 2 == 1) {
                ll A = (a + 1) / 2, B = a - A;

                if (small)
                    swap(A, B);
                cout << A << " " << B << "\n";
            }
            else
                cout << "Bachelor Number." << "\n";
        }
    }
}