#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

struct point {
    double x, y;
    point() {}
    point(double X, double Y) {x = X, y = Y;}
};

point farmer;

double get_angle(point a) {return atan2(a.y - farmer.y, a.x - farmer.x);}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, r;
    cin >> n >> r;
    cin >> farmer.x >> farmer.y;
    vector<pdd> intervals;
    for (int i = 0; i < r; i++) {
        int p;
        cin >> p;
        vector<point> points(p);
        for (int j = 0; j < p; j++)
            cin >> points[j].x >> points[j].y;
        for (int j = 0; j < p; j++)
        {

        }
    }
}