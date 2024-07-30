#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

// malkice je kompleksan kod, nisam brojao inverzije na klasican nacin
// bukvalno sam gledao za svaki podniz koji pocinje u nekom i
// koliko ima drugih indeksa koji su veci od cumsum[i]
// to radim pomocu segmentnog
// posto neke vrijednost mogu bit negativne, samo dodajem n na svaku vrijednost


// iterativna implementacija segmentnog
struct seggy { 
    vector<int> tree;
    int n;
    seggy(int siz) {
        n = siz;
        tree.resize(n * 2, 0);
    }
    
    int query(int l, int r) {
        int sum = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) 
                sum += tree[l++];
            if (r & 1)
                sum += tree[--r];
        }

        return sum;
    }

    void mod(int p, int val) {
        for (p += n; p > 0; p /= 2)
            tree[p] += val;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    seggy gaming(2 * n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if (arr[i] < k)
            arr[i] = 1;
        else
            arr[i] = -1;
    }

    // n is the 0
    gaming.mod(arr[0] + n, 1);
    for (int i = 1; i < n; i++)
    {
        arr[i] += arr[i - 1];
        gaming.mod(arr[i] + n, 1);
    }
    
    ll modifier = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += gaming.query(n + modifier, 2 * n - 1);
        modifier = arr[i];
        gaming.mod(arr[i] + n, -1);
    }

    cout << (ll)n * (ll)(n + 1) / 2LL - cnt << "\n";
}
