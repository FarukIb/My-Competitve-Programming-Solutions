#include <bits/stdc++.h>
//#include "homecoming.h"
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll INF = 1e18;


ll n, k;

ll cmp1(pii a, pii b) {return a.first < b.first;}

ll solve(int N, int K, int *A, int *B) {
    n = N, k = K;
    vector<ll> cost(n);
    cost[0] = B[0];
    for (int i = 1; i < n; i++)
        cost[i] = (ll)B[i] + cost[i - 1];
    vector<vector<ll> > dp(n, vector<ll>(2, -INF));
    // take 1
    dp[0][1] = (ll)A[0] - cost[k - 1];
    for (ll i = 1; i < n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        ll val_continue = dp[i - 1][1] + (ll)A[i];
        if (i + k - 1 < n)
            val_continue -= (ll)B[i + k - 1, i + k - 1];
        ll val_begin_new = dp[i - 1][0] + (ll)A[i] - (cost[min(i + k - 1, n - 1)] - cost[i - 1]);
        dp[i][1] = max(val_continue, val_begin_new);
    }

    ll out = max(dp[n - 1][0], dp[n - 1][1]);

    dp = vector<vector<ll> >(n, vector<ll>(2, -INF));
    dp[0][0] = 0;
    for (ll i = 1; i < n; i++)
    {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        ll val_continue = dp[i - 1][1] + (ll)A[i];
        val_continue -= (ll)B[(i + k - 1) % n];

        ll val_begin_new = dp[i - 1][0] + (ll)A[i] - (cost[min(i + k - 1, n - 1)] - cost[i - 1]);
        if (i + k - 1 >= n)
            val_begin_new -= cost[(i + k - 1) % n];
        dp[i][1] = max(val_continue, val_begin_new);
    }

    return max(out, max(dp[n - 1][0], dp[n - 1][1]));
}

int main() {
  ll T; assert(scanf("%d", &T) == 1);
  for(ll t = 0; t < T; t++) {
    ll N, K; assert(scanf("%d%d", &N, &K) == 2);
    int *A = new int[N];
    int *B = new int[N];
    for(ll i = 0; i < N; i++) assert(scanf("%d", &A[i]) == 1);
    for(ll i = 0; i < N; i++) assert(scanf("%d", &B[i]) == 1);
    printf("%lld\n", solve(N, K, A, B));
    delete[] A;
    delete[] B;
  }
  return 0;
}
