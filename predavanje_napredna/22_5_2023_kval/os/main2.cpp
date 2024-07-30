#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    map<ll, int> mapp;

    mapp[10000000000] = 12321;

    mapp["asdasd"] = 3;

    mapp["asdsadas"] = 2;

    cout << mapp["asdasd"] + mapp["asdsadas"] << "\n";

    mapp.count(12321312);
}