#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

const ld eps = 1e-6;
const ld inf = 1e12;

struct linear_func {
    ld m, b;
    ld mass;
    int idx;

    linear_func() {}
    linear_func(ld M, ld B, ld MASS, int IDX) {m = M, b = B, mass = MASS, idx = IDX;}

    ld evaluate(ld x) {
        return m * x + b;
    }

    bool operator<(const linear_func& x) const {
        return b < x.b;
    }
};

double collision_time(linear_func f, linear_func g) {
    if (abs(g.m - f.m) < eps)
        return inf;
    return (f.b - g.b)/(g.m - f.m);
}

vector<linear_func> get_after_collisions(linear_func f, linear_func g) {
    ld place = f.evaluate(collision_time(f, g));

    ld m1 = ((f.mass - g.mass) * f.m + 2.0 * g.mass * g.m)
            / (f.mass + g.mass);
    ld m2 = ((g.mass - f.mass) * g.m + 2.0 * f.mass * f.m)
            / (f.mass + g.mass);

    linear_func f1(m1, place, f.mass, f.idx);
    linear_func f2(m2, place, g.mass, g.idx);
    vector<linear_func> out = {f1, f2};
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; ld t;
    cin >> n >> t;

    vector<linear_func> balls(n);
    for (int i = 0; i < n; i++)
    {
        cin >> balls[i].b >> balls[i].m >> balls[i].mass;
        balls[i].idx = i;
    }
    
    sort(balls.begin(), balls.end());

    ld time = 0;
    while (time < t) {
        ld earliest_time = inf;
        vector<int> collisions;
        for (int i = 0; i < n - 1; i++) {
            ld time_of_meeting = collision_time(balls[i], balls[i + 1]);
            if (time_of_meeting - eps < 0)
                continue;
            
            if (earliest_time > time_of_meeting)
            {
                collisions.clear();
                collisions.push_back(i);
                earliest_time = time_of_meeting;
            }
            else if (abs(earliest_time - time_of_meeting) < eps) {
                collisions.push_back(i);
            }
        }

        vector<bool> marked(n, false);
        for (int i = 0; i < collisions.size(); i++)
            marked[collisions[i]] = true;

        if (earliest_time + time > t)
            break;
        for (int i = 0; i < n; i++) {
            if (marked[i] == true)
            {
                vector<linear_func> neww = get_after_collisions(balls[i], balls[i + 1]);
                balls[i] = neww[0];
                balls[i + 1] = neww[1];

                i++;
                continue;
            }
            
            balls[i].b = balls[i].evaluate(earliest_time);
        }
        time += earliest_time;
    }

    vector<ld> out(n);
    for (int i = 0; i < n; i++)
        out[balls[i].idx] = balls[i].evaluate(t - time);

    for (int i = 0; i < n; i++)   
        cout << fixed << setprecision(5) << out[i] << "\n";
}