#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, br = 0;
    cin >> n;
    for (int i = 1; i < 1000; i++) {
        string s = bitset<32>(i).to_string();
        int k = stoi(s);
        if (k <= n)
            br++;
    }   
    cout << br << "\n";
}