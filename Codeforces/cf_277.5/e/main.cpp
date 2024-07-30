#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<double> xs;
vector<double> beauty;
vector<vector<double> > dists;
int n; double l;

vector<double> path;
double get_val(double r, bool trace_path) {
    vector<int> pnt(n, -1);
    vector<double> mini(n, 1e9); mini[0] = 0;
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--) {
            double val = mini[j] + dists[i][j] - beauty[i] * r;
            if (val < mini[i])
                mini[i] = val, pnt[i] = j;
        }
    }
    if (trace_path) {
        path.push_back(n - 1);
        int curr = n - 1;
        while (curr != 0) {
            curr = pnt[curr];
            if (curr != 0)
                path.push_back(curr);
        }
        reverse(all(path));
    }
    return mini[n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> l;
    n++;
    xs = vector<double>(n, 0.0);
    beauty = vector<double>(n);

    dists = vector<vector<double> >(n, vector<double>(n));
    for (int i = 1; i < n; i++)
        cin >> xs[i] >> beauty[i];
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            dists[i][j] = sqrt(abs(abs(xs[i] - xs[j]) - l));

    double l = 0, r = 1e12;
    while (r - l > 1e-10) {
        double mid = (l + r) / 2;
        if (get_val(mid, false) < 0)
            r = mid;
        else
            l = mid;
    }
    get_val(l, true);
    for (int s : path)  
        cout << s << " ";
    cout << "\n";
}