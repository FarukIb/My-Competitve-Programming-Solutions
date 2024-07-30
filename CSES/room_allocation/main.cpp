#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct event {
    int tim, idx;
    int appear;

    bool operator<(const event& b) const {
        if (tim == b.tim)
            return appear > b.appear;
        return tim < b.tim;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<event> events;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        events.push_back({a, i, 1});
        events.push_back({b, i, -1});
    }
    sort(all(events));
    
    vector<int> room(n);
    queue<int> fre; int num = 1;
    for (event e : events) {
        if (e.appear == -1)
            fre.push(room[e.idx]);
        else {
            if (fre.empty()) 
                room[e.idx] = num++;
            else {
                room[e.idx] = fre.front();
                fre.pop();
            }
        }
    }

    cout << num - 1 << endl;
    for (int i = 0; i < n; i++)
        cout << room[i] <<" ";
    cout << endl;
}