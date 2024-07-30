#include <bits/stdc++.h>
#include "make.cpp"
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int num = 1; num <= 10; num++) {
        string name = to_string(num);
        if (num < 10)
            name = "0" + name;
        ifstream fin("./tests/" + name + ".in");
        int n;
        fin >> n;
        vector<pii> points(n);
        for (int i = 0; i < n; i++) 
            fin >> points[i].first >> points[i].second;
        vector<pii> out = make(points);

        ofstream fout("./outs/" + name + ".out.txt");
        fout << out.size() << "\n";
        for (pii o : out)
            fout << o.first << " " << o.second << "\n";
    }
}