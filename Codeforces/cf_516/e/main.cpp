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

    int w = -1, b;

    int srch[2] = {1, (int)1e9};

    cout << "0 0" << endl;
    string typ;
    cin >> typ;
    if (typ == "black")
        w = 1, b = 0;
    else
        w = 0, b = 1;
    
    n--;
    while (n--)
    {
        int mid = (srch[0] + srch[1]) / 2;

        cout << mid << " " << "1" << endl;

        string type;
        cin >> type;
        
        if (type == "black")
            srch[b] = mid;
        else
            srch[w] = mid;
    }

    int mid = (srch[0] + srch[1]) / 2;
    cout << srch[0] << " 2 " << srch[1] << " 0" << endl;
}
