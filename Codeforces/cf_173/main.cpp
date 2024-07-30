#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll highest = 41;

struct node {
    node* on;
    node* off;
    node* par;
    int num_on, num_off;

    node() { on = nullptr, off = nullptr, par = nullptr, num_on = 0, num_off = 0; }
    node(node* parr) { par = parr, on = nullptr, off = nullptr, par = nullptr, num_on = 0, num_off = 0; }
};

node* root = new node();

void insert(ll num) {
    node* curr = root;
    for (ll bit = highest; bit >= 0; bit--) {
        node* my;
        if ((1LL << bit) & num) {
            if (curr->on == nullptr)
                my = new node(curr);
            else
                my = curr->on;
            curr->on = my;
            curr->num_on++;
            curr = my;
        }
        else {
            if (curr->off == nullptr)
                my = new node(curr);
            else
                my = curr->off;
            curr->off = my;
            curr->num_off++;
            curr = my;
        }
    }
}

void remov(ll num) {
    node* curr = root; 
    for (ll bit = highest; bit >= 0; bit--) {
        if ((1LL << bit) & num)
            curr->num_on--, curr = curr->on;
        else
            curr->num_off--, curr = curr->off;
    }
}

ll query(ll num) {
    node* curr = root;
    ll g = 0;
    for (ll bit = highest; bit >= 0; bit--) {
        // on
        if (curr->num_off == 0 || ((1LL << bit) & num) == 0 and curr->num_on != 0) {
            g += 1LL << bit;
            curr = curr->on;
        } else { // offs
            curr = curr->off;
        }
    }
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    vector<ll> pref(n + 1, 0);
    vector<ll> suff(n + 1, 0);
    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] ^ arr[i];
    insert(0);
    for (int i = n - 1; i >= 0; i--)
    {
        suff[i] = suff[i + 1] ^ arr[i];
        insert(suff[i]);
    }

    ll out = query(0);
    for (int i = 0; i < n; i++) {
        remov(suff[i]);
        ll bestt = query(pref[i]);
        out = max(pref[i] ^ bestt, out);
    }

    cout << out << "\n";
}