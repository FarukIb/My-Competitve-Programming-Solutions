#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()
#define x first 
#define y second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> point;
typedef pair<point, point> line;

const double eps = 1e-4;

bool is_vertical(line a) {
    if (a.first.x == a.second.x)
        return true;
    return false;
}

bool is_on_ine(line a, point b) {
    if (a.first.x - eps <= b.first and a.second.x + eps >= b.x)
        return true;
    return false;
}

double getM(line a) {
    double M = (a.first.y - a.second.y)/(a.first.x - a.second.x);
    return M;
}

double getB(line a) {
    double M = getM(a);
    double B = a.first.y - M*a.first.x;
    return B;
}

double get_line_y(line a, double b) {
    double M = getM(a);
    double B = getB(a);

    return M*b + B;
}

point line_line(line a, line b) {
    double b2 = getB(b);
    double b1 = getB(a);
    double m1 = getM(a);
    double m2 = getM(b);
    double pointX = (b1 - b2) / (m2 - m1);
    double pointY = get_line_y(a, pointX);
    return point(pointX, pointY);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    line a, b;
    cin >>a.first.x >> a.first.y >> a.second.x >> a.second.y;
    cin >>b.first.x >> b.first.y >> b.second.x >> b.second.y;
    if (a.first > a.second)
        swap(a.first, a.second);
    if (b.first > b.second)
        swap(b.first, b.second);

    if (is_vertical(a) and is_vertical(b))
    {
        cout << "NE\n";
        return 0;
    }
    point inter;
    if (is_vertical(b))
        swap(a, b);
    if (is_vertical(a)) {
        inter.x = a.first.x;
        inter.y = get_line_y(b, a.first.x);
    } else {
        if (abs(getM(a) - getM(b)) <= eps)
        {
            cout << "NE\n";
            return 0;
        }
        inter = line_line(a, b);
    }

    if (is_on_ine(a, inter) and is_on_ine(b, inter))
        cout << round(inter.first) << " " << round(inter.second) << "\n";
    else
        cout << "NE\n";
}