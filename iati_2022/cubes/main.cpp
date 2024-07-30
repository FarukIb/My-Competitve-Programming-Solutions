#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const ll maxn = 4e5;

ll bin_expo(ll base, ll xp) {
    if (xp == 0)
        return 1;
    ll half = bin_expo(base, xp / 2);
    half = half * half % mod;
    if (xp % 2)
        half = half * base % mod;
    return half;
}

ll mod_inv(ll a) {
    return bin_expo(a, mod - 2);
}

ll add(ll a, ll b) {
    return (((a % mod) + (b % mod)) % mod + mod) % mod;
}

ll mult(ll a, ll b) {
    return (((a % mod) * (b % mod)) % mod + mod) % mod;
}

vector<ll> fact, invfact;
void init() {
    fact = invfact = vector<ll> (maxn, 1);
    for (int i = 1; i < maxn; i++)
        fact[i] = mult(fact[i - 1], i);
    invfact[maxn - 1] = mod_inv(fact[maxn - 1]);
    for (int i = maxn - 2; i >= 0; i--)
        invfact[i] = mod_inv(fact[i]);
}

ll bin_coef(ll n, ll k) {
    return mult(fact[n], mult(invfact[k], invfact[n - k]));
}

int n;
vector<vector<int> > graph, bi;
vector<bool> is_root, visited;
vector<int> subt_size;

void add_edge(int a, int b) {
    graph[a].push_back(b);
    bi[a].push_back(b);
    bi[b].push_back(a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();
    int k;
    cin >> n >> k;
    graph = bi = vector<vector<int> > (n + 1);
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    // make graph
    // step 1, connect bigs
    vector<int> order(n);
    vector<int> bigs;
    for (int i = 0; i < n; i++)
        if (arr[i] * 2 > k)
            bigs.push_back(i), order[i] = bigs.size();
    for (int i = 1; i < bigs.size(); i++)
        add_edge(bigs[i - 1], bigs[i]);
    // step 2, connect bigs with smalls
    for (int i = 0; i < bigs.size(); i++) {
        int r;
        if (i == bigs.size() - 1)
            r = n;
        else
            r = bigs[i + 1];
        for (int j = bigs[i] + 1; j < r; j++)
            if (arr[bigs[i]] + arr[j] > k)
                add_edge(bigs[i], j);
    }
    
   // step 3 connect smalls with bigs, can be optimized
    for (int i = 0; i < n; i++) {
        if (arr[i] * 2 > k)
            continue;
        for (int j = i + 1; j < n; j++) { // j must be big
            if (arr[i] + arr[j] > k)
            {
                add_edge(i, j);
                break;
            }
        }
    }

    // count empty islands
    ll num_empty_islands = 0;
    for (int i = 0; i < n; i++) 
        if (bi[i].empty() and !(arr[i] *2 > k))  
            num_empty_islands++;
    
    // count non-dependants
    ll num_non_dependant = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] * 2 > k)
            continue;
        if (graph[i].empty() and !bi[i].empty())
        {
            num_non_dependant++;
            bi[i].clear();
            graph[i].clear();
        }
    }
    
    // now count the interval guys
    ll interval_prod = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] * 2 > k)
            continue;
        if (bi[i].size() == 2)
            interval_prod = mult(interval_prod, abs(bi[i][0] - bi[i][1]));
    }

    cout << mult(mult(bin_coef(n, num_empty_islands), fact[num_empty_islands]), mult(fact[num_non_dependant], interval_prod)) << "\n";
}