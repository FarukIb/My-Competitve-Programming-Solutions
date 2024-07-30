#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct median {
    ll lsum, rsum;
    multiset<int> l;
    multiset<int> r;

    median() {lsum = 0, rsum = 0;}

    ll get_med() {
        return *prev(l.end());
    }

    void balance() {
        if (l.size() > r.size() and (l.size() + r.size() % 2) == 0 ||
            l.size() > r.size()+1) { // ako iz prvog u drugog
            int a = *prev(l.end());
            l.erase(l.find(a));
            lsum -= a;
            r.insert(a);
            rsum += a;
        }
        if (r.size() > l.size()) {
            int a = *r.begin();
            r.erase(r.begin());
            rsum -= a;
            l.insert(a);
            lsum += a;
        }
    }

    void insert(int x) {
        if (l.empty() || x >= get_med())
        {
            r.insert(x);
            rsum += x;
        }
        else
        {
            l.insert(x);
            lsum += x;
        }
        balance();
    }

    void rem(int x) {
        if (l.find(x) != l.end()) {
            l.erase(l.find(x));
            lsum -= x;
        } else {
            r.erase(r.find(x));
            rsum -= x;
        }
        balance();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<ll> arr(n);
    vector<ll> cumsum(n+1);
    for (int i = 0; i < n; i++) 
    {
        cin >> arr[i];
        cumsum[i + 1] = arr[i] + cumsum[i];
    }
    median med;
    for (int i = 0; i < k - 1; i++)
    {
        med.insert(arr[i]);
    }
    
    for (int i = k - 1; i < n; i++) {
        med.insert(arr[i]);
        cout << (ll)med.get_med()*med.l.size() - med.lsum + 
        (med.rsum - (ll)(med.get_med()*med.r.size())) << " ";

        med.rem(arr[i - k + 1]);
    }
    cout << endl;
}