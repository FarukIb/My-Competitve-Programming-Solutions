// now, i feel like this task is ment to be solved with a certain type of self balancing BST
// but, since the task is offline we can use coordinate compression and fenwick tree

// first step, compress the array you get (look up array/coordinate compression if you do not know what it is)
// then use a fenwick tree to dynamically find out how many elemnts appeared 
// before the current elemnt(look at the code at line 90 for explanation)
// after that, just take their average

#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define pii pair<int, int>
#define ll long long

using namespace std;

struct bit
{
    vector<int> tree;
    int n;

    bit(int N)
    {
        n = N;
        tree.resize(n + 1, 0);
    }

    void add(int idx, int val)
    {
        idx++;
        while (idx <= n)
            tree[idx] += val, idx += idx & (- idx);
    }

    int get(int idx)
    {
        idx++;
        int out = 0;
        while (idx > 0)
            out += tree[idx], idx -= idx & (-idx);
        return out;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<pii> ar;
    double out = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        ar.push_back(pii(x, i));
    }

    // coordinate compression
    vector<pii> arr = ar;
    sort(arr.begin(), arr.end());

    map<int, int> keys;
    keys[arr[0].first] = 0;
    int curr = 1;
    for (int i = 1; i < n; i++)
    {
        if (arr[i].first == arr[i - 1].first)
            continue;
        keys[arr[i].first] = curr;
        curr++;
    }

    vector<int> arr2(n);
    for (int i = 0; i < n; i++)
        arr2[i] = keys[ar[i].first];

    // calculating part
    bit bit(n + 1);
    for (int i = 0; i < n; i++)
    {
        out += (i + 1 - bit.get(arr2[i]));
        bit.add(arr2[i], 1);
    }

    out /= n;
    cout << fixed << setprecision(2) << out << endl;
}