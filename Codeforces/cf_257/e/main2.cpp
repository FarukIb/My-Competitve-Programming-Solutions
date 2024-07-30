#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool cmp(pii a, pii b) {return  (__gcd(a.first, a.second) >= __gcd(b.first, b.second)) ? (__gcd(a.first, a.second) == __gcd(b.first, b.second) ? a < b : false) : true; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<pii> in(44);
    for (int i = 0; i<44; i++)   
    {
        cin >> in[i].first >> in[i].second;
        if (in[i].first > in[i].second)
            swap(in[i].first, in[i].second);
    }
    sort(in.begin(), in.end(), cmp);
    cout << endl;
    for (pii i : in)
        cout << i.first << " " << i.second << " GCD: " << __gcd(i.first, i.second) << "\n";
}