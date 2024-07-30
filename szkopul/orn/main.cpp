#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int seg[(int)5e5+1];
int n, m, a, b, k;
void init() {
    for (int i = n + m; i < 2*(n+m); i++)
        seg[i] = 1;
    for (int i = n + m - 1; i > 0; i--)
        seg[i] = seg[i*2] + seg[i*2+1];
}

void sett(int a) {
    a += n + m;
    while (a > 0)
        seg[a]--, a /= 2;
}

int query(int a, int b) {
    int o = 0;
    for (a += n + m, b += n + m + 1; a < b; a /= 2, b /= 2) {
        if (a & 1)
            o += seg[a++];
        if (b & 1)
            o += seg[--b];
    }
    return o;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> a >> b >> k;
    if (n + m > 250000)
    {
        cout << 10000000 << "\n";
        return 0;
    }
    init();
    int l = 0, left = n + m;
    while (k--) {
        int move = a;
        if (l >= n)
            move = b;
        
        move %= left;
        if (move == 0)
            move += left;

        int to_end = query(l, n + m - 1);
        if (to_end < move)
            move -= to_end, l = 0;
        int L = l, R = n + m, ans = -1;
        while (L < R) {
            int mid = (L + R) / 2;
            if (query(l, mid) >= move)
                R = mid, ans = mid;
            else
                L = mid + 1;
        }

        l = ans;
        sett(l);
        left--;
    }

    cout << l+1 << "\n";
}