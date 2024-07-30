#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct pt {
    double x, y;

    bool operator<(const pt& b) const {
        if (y == b.y)
            return x < b.x;
        return y < b.y;
    }

    pt() {}
    pt(double X, double Y) {x = X, y = Y;}
};

double cmp2(pt a, pt b) {return a.x < b.x;}
double ori(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
}

pt p0;
bool cmp(pt a, pt b) {
    return (ori(p0, a, b) < 0.0);
}
    
vector<pt> hull(int n, vector<pt> points) {
    sort(points.begin(), points.end());
    p0 = points[0];
    sort(points.begin(), points.end(), cmp);

    vector<pt> st;
    for (int i = 0; i < n; i++) {
        if (st.size() > 1 && ori(st[st.size() - 2], st.back(), points[i]) > 0.0)
            st.pop_back();
        st.push_back(points[i]);
    }

    return st;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pt> points(n);
    for (int i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y;
    
    vector<pt> ans = hull(n, points);
    for (pt x : ans) 
        cout << x.x << " " << x.y << endl;
}
