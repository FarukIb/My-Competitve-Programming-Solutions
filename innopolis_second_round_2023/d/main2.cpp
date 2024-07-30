#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;

const ll siz = 10;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int R;
    cin >> R;
    if (R == 1) {
        int n;
        cin >> n;
        string out;
        for (int i = 0; i < n; i++) {
            int o;
            cin >> o;
            if (i % 2)
            out += (bitset<siz>(o - 1).to_string());
        }
        cout << out << endl;
        return 0;
    }
    int n;
    cin >> n;
    vector<int> perm(n);
    for (int i = 0; i < n; i++)
        cin >> perm[i];
     
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i += 10) {
        int c = 0;
        for (int b = 0; b < 10; b++)
            if (s[i + b] == '1')
                c += 1 << (9 - b);
        cout << c + 1 << " ";
    }
    cout << endl;
}