#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int out = 0;
void reset(vector<int> &sett, int to_rem, int neww, bool dec) {

    if (to_rem != 0 && sett[to_rem - 1] > sett[to_rem] and !dec)
        out--;
    if (to_rem != sett.size() - 1 && sett[to_rem] > sett[1+to_rem] and !dec)
        out--;

    if (to_rem != 0 && (sett[to_rem - 1] > neww))
        out++;
    if (to_rem != sett.size() - 1 && neww > sett[to_rem + 1])
        out++;
    sett[to_rem] = neww;
}

void sw(vector<int> &sett, int f, int s) {
    int fv = sett[f];
    reset(sett, f, sett[s], false);
    reset(sett, s, fv, false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    vector<int> neww(n);
    for (int i = 0; i < n; i++)
    {
        cin >>arr[i]; arr[i]--;
        reset(neww, arr[i], i,true);
    }
    out = 1;

    for (int i = 1; i<n ; i++)
        if (neww[i] < neww[i - 1])
            out++;

    while (q--) {
        int f, t;
        cin >> f >>t;
        sw(neww, arr[f-1], arr[t-1]);
        swap(arr[f - 1], arr[t - 1]);
        cout << out << "\n";
    }
}