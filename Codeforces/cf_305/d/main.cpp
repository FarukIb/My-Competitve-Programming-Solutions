#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct seggy {
    int n;
    vector<int> tree;
    
    seggy() {}
    seggy(vector<int> arr) {
        n = arr.size();
        tree.resize(n * 2);
        for (int i = n; i < 2 * n; i++)
            tree[i] = arr[i - n];
        for (int i = n - 1; i > 0; i--)
            tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }

    int query(int l, int r) {
        int mini = 1e9;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                mini = min(mini, tree[l++]);
            if (r & 1)
                mini = min(mini, tree[--r]);
        }
        return mini;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    seggy seg(arr);
    
    vector<int> outt(n + 1, 0);
    for (int i = 0; i < n; i++) {

        int l = 0, r = i;
        while (l < r) {
            int mid = (l + r) / 2;
            if (seg.query(mid, i) >= arr[i])
                r = mid;
            else
                l = mid + 1;
        }
 
        int leftt = l;
        if (seg.query(leftt, i) < arr[i] && arr[i - 1] && leftt != i)
            leftt++;

        l = i, r = n - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (seg.query(i, mid) >= arr[i])
                l = mid + 1;
            else
                r = mid;
        }

        int rightt = l;
        if (seg.query(i, rightt) < arr[i] && rightt != i)
            rightt--;

        outt[rightt - leftt + 1] = max(outt[rightt - leftt + 1], arr[i]);
    }

    for (int i = n - 1; i > 0; i--) {
        outt[i] = max(outt[i], outt[i + 1]);
    }

    for (int i = 1; i <= n; i++)
        cout << outt[i] << " ";
    cout << "\n";
}
