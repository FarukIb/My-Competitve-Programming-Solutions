#include <bits/stdc++.h>    	
#define all(a) a.begin(), a.end()

using namespace std;

typedef pair<int, int> pii;

const int C = 80;
const int MAXN = 1e5+1;
const int MAXU = 2e5+1;

int n, d, u;
vector<int> heights(MAXN);
vector<pii> changes(MAXU);

int min_dist(vector<int> first, vector<int> second) {
    if (first.empty() || second.empty())
        return 1e9;
    for (int i = 0; i < first.size(); i++)
        first[i] = heights[first[i]];
    for (int i = 0; i <second.size(); i++)
        second[i] = heights[second[i]];
    sort(all(first));
    sort(all(second));

    int pnt1 = 0, pnt2 = 0, out = 2e9;
    while (pnt1 < first.size() and pnt2 < second.size()) {
        out = min(out, abs(first[pnt1] - second[pnt2]));

        if (pnt1 + 1 == first.size())
            pnt2++;
        else if (pnt2 + 1 == second.size())
            pnt1++;
        else if (first[pnt1] < second[pnt2])
            pnt1++;
        else
            pnt2++;
    }
    return out;
}

vector<int> state_tim[MAXN];
vector<vector<int> > state_set[MAXN];
vector<pii> individ_updates[MAXN];
void init(int N, int D, int H[]) {
    n = N;
    for (int i = 0; i < n; i++)
    {
        heights[i] = H[i];
        state_tim[i].push_back(-1);
        state_set[i].push_back(vector<int>());
    }
    d = D;
}

void process(set<int> &set, int &val) {
    if (set.count(val))
        set.erase(val);
    else
        set.insert(val);
}

void curseChanges(int U, int A[], int B[]) {
    u = U;
    for (int i = 0; i < u; i++)
    {
        changes[i].first = A[i], changes[i].second = B[i];
        individ_updates[A[i]].push_back({i, B[i]});
        individ_updates[B[i]].push_back({i, A[i]});
    }
    
    vector<int> time_since_last(n, 0);
    vector<set<int> > guys(n);
    for (int i = 0; i < u; i++) {
        int a = changes[i].first, b = changes[i].second;
        process(guys[a], b);
        process(guys[b], a);
        if (time_since_last[a] == C) {
            state_tim[a].push_back(i);
            state_set[a].push_back(vector<int>(all(guys[a])));
            time_since_last[a] = 0;
        }
        if (time_since_last[b] == C) {
            state_tim[b].push_back(i);
            state_set[b].push_back(vector<int>(all(guys[b])));
            time_since_last[b] = 0;
        }
        time_since_last[a]++;
        time_since_last[b]++;
    }
}

vector<int> get_set(int x, int v) {
    int check_tim_idx = upper_bound(all(state_tim[x]), v) - state_tim[x].begin() - 1;
    set<int> guys(all(state_set[x][check_tim_idx]));
    int idx = lower_bound(all(individ_updates[x]), 
        pii(state_tim[x][check_tim_idx], 1e9)) - individ_updates[x].begin();
    
    for (; idx < individ_updates[x].size() and individ_updates[x][idx].first < v; idx++)
        process(guys, individ_updates[x][idx].second);
    return vector<int>(all(guys));
}

int question(int x, int y, int v) {
    vector<int> x_set = get_set(x, v), y_set = get_set(y, v);
    return min_dist(x_set, y_set);
}
