#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int m, k;
    cin >> m >> k;

    vector<string> blo;
    vector<string> des;

    string a;
    cin >> a;
    string curr = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '|')
            blo.push_back(curr), curr = "";
        else
            curr += a[i];
    }
    blo.push_back(curr), curr = "";

    cin >> a;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '|')
            des.push_back(curr), curr = "";
        else
            curr += a[i];
    }
    des.push_back(curr), curr = "";

    // processing
    int tim = 0;
    for (int i = 0; i < m; i++) {
        bool needtowait = false;
        for (int j = 0; j < k; j++) 
            if (des[i][j] == '1' && blo[i][j] == '0')
                needtowait = true;
        
        if (needtowait)
        {
            tim += 100;
            for (int j = 0; j < k; j++)
                blo[i][j] = '1';
        }

        for (int j = 0; j < k; j++) 
            if (des[i][j] != blo[i][j])
                tim++;
    }

    cout << tim << "\n";
}
