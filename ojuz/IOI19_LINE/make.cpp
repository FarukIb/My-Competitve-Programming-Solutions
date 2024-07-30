#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

ll dist(pii a, pii b) { return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second); }

vector<pii> make(vector<pii> points) {
    sort(all(points));
    pii last(0,0);
    vector<pii> out;
    while (!points.empty()) {
        int n = points.size();
        vector<bool> used(n);
        used[0] = true;
        // getting direction
        int up = 0, down = 0;
        for (int i = 1; i < n; i++) 
        {
            if (points[i].s > points[0].s)
                up++;
            else
                down++;
        }

        bool goup = true;
        if (down > up)
            goup = false;

        vector<pii> streak; ll lidx = 0;
        streak.push_back(points[0]);
        while (1) {
            ll mindx, minval = 1e18;
            for (int i = lidx + 1; i < n; i++) {
                if ((points[i].first - points[lidx].first) * (points[i].first - points[lidx].first) > minval)
                    break;
                if (goup and points[i].second < points[lidx].second)
                    continue;
                if (!goup and points[i].second > points[lidx].second)
                    continue;
                ll distt = dist(points[lidx], points[i]);
                if (distt < minval)
                    minval = distt, mindx = i;
            }
            if (minval == 1e18)
                break;
            lidx = mindx;
            used[mindx] = true;
            streak.push_back(points[mindx]);
        }
        if (goup)
            out.push_back(mp(streak[0].first, last.second));
        else
            out.push_back(mp(last.first, streak[0].second));
        out.push_back(streak[0]);
        if (streak.size() != 1)
        {
            out.push_back(mp(streak[0].first, streak[1].second));
            for (int i = 1; i < streak.size() - 1; i++) {
                if ((i) % 2)
                    out.push_back(mp(streak[i+1].first, streak[i].second));
                else
                    out.push_back(mp(streak[i].first, streak[i+1].second));
            }
        }
        last = streak[streak.size() - 1];
        out.push_back(last);

        vector<pii> newp;
        for (int i = 0; i < n; i++)
            if (!used[i])
                newp.push_back(points[i]);
        points = newp;
    }

    vector<pii> out2;
    out2.push_back(out[0]);
    for (int i = 1; i < out.size() - 1; i++) {
        if (out[i].first == out[i - 1].first and out[i].first == out[i + 1].first)
            continue;
        if (out[i].second == out[i - 1].second and out[i].second == out[i + 1].second)
            continue;
        out2.push_back(out[i]);
    }
    out2.push_back(out[out.size() - 1]);
    return out;
}