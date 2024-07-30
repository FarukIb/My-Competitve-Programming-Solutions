#include <bits/stdc++.h>
#include "molecules.h"

using namespace std;

#define all(a) a.begin(), a.end()

typedef long long ll;
typedef pair<int, int> pii;

std::vector<int> find_subset(int l, int u, std::vector<int> w) {
    int n = w.size();
    vector<pii> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].first = w[i];
        arr[i].second = i;
    }
    sort(all(arr));

    ll sum = 0, r = 0; int L = -1, R = -1;
    for (int i = 0; i < n; i++) {
        if (i != 0)
            sum -= arr[i - 1].first;
        while (r < n and sum < l) {
            sum += arr[r].first;
            r++;
        }
        if (sum >= l and sum <= u) {
            L = i, R = r;
        }
    }

    if (L == -1)
        return vector<int>(0);
    else {
        vector<int> idxs;
        for (int i = L; i < R; i++)
            idxs.push_back(arr[i].second);
        sort(all(idxs));
        return idxs;
    }
}
