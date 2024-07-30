#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxx = 1e5;
const int maxd = 5;
const int N = 26;

int fibs[N];
vector<bool> isfib(1e5+1);
void recur(int curr, int steps) {
    if (curr > maxx || isfib[curr])
        return;
    if (steps > 0)
        isfib[curr] = true;

    int my_siz = to_string(curr).size();
    for (int i = 0; i < N; i++) {
        if (to_string(fibs[i]).size() + my_siz > maxd)
            break;
        recur(stoi(to_string(curr) + to_string(fibs[i])), steps + 1);
    }
    recur(curr*10, steps + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    
    fibs[1] = 1, fibs[0] = 1;
    for (int i = 2; i < N; i++)
        fibs[i] = fibs[i - 2] + fibs[i - 1];

    for (int i = 0; i < N; i++)
        recur(fibs[i], 0);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (isfib[n])   
            cout << "YES\n";
        else
            cout <<"NO\n";
    }
}