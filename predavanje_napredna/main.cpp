#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seg {
    vector<int> t;
    int n;

    seg(vector<int>arr) {
        n = arr.size();
        t.resize(n * 2, 0);
        for (int i = n; i < 2 * n; i++)
            t[i] = arr[i - n];
        for (int i = n - 1; i > 0; i--)
            t[i] = t[i * 2] + t[i * 2 + 1];
    }

    int query(int l, int r) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out += t[l++];
            if (r & 1)
                out += t[--r];
        }
        return out;
    }

    void mod(int idx, int val) {
        idx += n;
        t[idx] = val;
        for (idx /= 2; idx > 0; idx /= 2) {
            t[idx] = t[idx * 2] + t[idx * 2 + 1];
        }
    }
};

int getans(int sum) {
    while (sum >= 10) {
        string s = to_string(sum);
        int new_sum = 0;
        for (char x : s)
            new_sum += x - '0';
        sum = new_sum;
    }

    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    vector<int> arr(s.size());
    for (int i = 0; i < s.size(); i++)
        arr[i] = s[i] - '0';
    seg seggy(arr);

    int q;
    cin >>q;
    while (q--) {
        int tip, a, b;
        cin >> tip >>a >> b;
        if (tip == 1) {
            a--, b--;

            cout << getans(seggy.query(a, b)) << "\n";
        }
        else {
            a--;
            s[a] = b + '0';
            seggy.mod(a, b);
        }
    }
}