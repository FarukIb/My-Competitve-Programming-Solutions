#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    ll out = 0;
    vector<int> arr(n);
    int num = 0;
    set<pii> events; 
    events.insert({-1, 0});
    events.insert({-1, 1});
    stack<pii> minstck;
    minstck.push({-1, -1});
    stack<pii> maxstck;
    maxstck.push({1e9, -1});
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while (minstck.top().first > x) {
            auto me = events.lower_bound({minstck.top().second, 0});
            auto prv = prev(me);
            auto nxt = next(me);
            num -= me->first - prv->first;
            if (nxt != events.end() and nxt->second == 0)
                num += nxt->first - prv->first;
            events.erase(me);
            minstck.pop();
        }
        minstck.push({x, i});
        num += i - events.rbegin()->first;
        events.insert({i, 0});

        while (maxstck.top().first < x) {
            auto me = events.lower_bound({maxstck.top().second, 1});
            auto prv = prev(me);
            auto nxt = next(me);
            if (nxt != events.end() and nxt->second == 0)
                num += me->first - prv->first;
            events.erase(me);
            maxstck.pop();
        }
        maxstck.push({x, i});
        events.insert({i, 1});

        out += num-1;
    }
    cout << out << "\n";
}