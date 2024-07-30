#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef set<pii>::iterator ite;

const int MX = 30;

void recur(int val, int left, vector<int> &arr) {
    if (left == 1)
    {
        arr.push_back(val);
        return;
    } else if (left == 2) {
        arr.push_back(val - 1);
        arr.push_back(val - 1);
        return;
    }
    int can_make_from_1 = 1 << (val - 1);
    if (can_make_from_1 >= left)
    {
        recur(val - 1, left - 1, arr);
        arr.push_back(val - 1);
    }
    else
    {
        recur(val - 1, can_make_from_1, arr);
        recur(val - 1, left - can_make_from_1, arr);
    }
}

vector<int> make(int val, int needed) {
    vector<int> out;
    recur(val, needed, out);
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    int needed = 1 << 30, lowest = 30;
    vector<int> og(n);
    vector<pii> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].second;
        og[i] = arr[i].second;
        arr[i].first = i;
        needed -= 1 << arr[i].second;
        lowest = min(lowest, arr[i].second);
    }
    needed = log2(needed);
    
    vector<vector<int> > to_insert(n+1);
    vector<pii> neww;
    for (; lowest < 30; lowest++) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].second == lowest) {
                int s = 0, j;
                for (j = i; j < arr.size() && arr[j].second == lowest; j++)
                {
                    s++;
                    if (s % 2)
                        neww.push_back({arr[j].first, lowest + 1});
                }
                if (s % 2)
                {
                    to_insert[arr[i].first].push_back(lowest);
                    k--;
                }
                i = j - 1;
            } else {
                neww.push_back(arr[i]);
            }
        }
        arr.clear();
        sort(all(neww));
        swap(neww, arr);
    }

    for (int i = 0; i <= n; i++) {
        reverse(all(to_insert[i]));
        if (k == 0)
            continue;
        vector<int> neww;
        for (int a : to_insert[i]) {
            if (k == 0) {
                neww.push_back(a);
                continue;
            }
            int possible = (1 << a);
            int to_make = min(possible, k) + 1;
            vector<int> compose = make(a, to_make);
            neww.insert(neww.end(), all(compose));
            k++;
            k -= to_make;
        }
        to_insert[i] = neww;
    }

    vector<int> out;
    for (int i = 0; i < n; i++) {
        out.insert(out.end(), all(to_insert[i]));
        out.push_back(og[i]);
    }
    for (int a : out) 
        cout << a << " ";
    cout << "\n";
}