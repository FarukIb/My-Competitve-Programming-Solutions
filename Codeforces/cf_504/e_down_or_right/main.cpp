#include <bits/stdc++.h>

using namespace std;

bool query(int x1, int y1, int x2, int y2) {
    cout << "? " << y1 << " " << x1 << " " << y2 << " " << x2 << endl;

    string ans;
    cin >> ans;
    return ans == "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    // PHASE 1 : TOP TO BOTTOM
    string first = "";
    int x = 1, y = 1;

    for (int s = 1; s < n; s++) {
        if (query(x, y + 1, n, n))
            y++, first += 'D';
        else
            x++, first += 'R';
    }

    // PHASE 2: BOTTOM TO BOTTOm
    string second = "";
    x = n, y = n;
    for (int s = 1; s < n; s++) {
        if (query(1, 1, x - 1, y))
            x--, second += 'R';
        else
            y--, second += 'D';
    }
    reverse(second.begin(), second.end());

    cout << "! " + first + second << endl;
}