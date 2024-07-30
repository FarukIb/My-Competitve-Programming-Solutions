#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxa = 1e7 + 10;
vector<ll> primes;
void get_primes() {
    vector<bool> sito(maxa, false);
    for (ll i = 2; i < maxa; i++) {
        if (sito[i])
            continue;
        primes.push_back(i);
        for (ll j = i * i; j < maxa; j += i)
            sito[j] = true;
    }
}

ll num_primes = 100;
ll get_cnt(ll fact, ll prime) {
    ll out = 0;
    for (ll guy = prime; guy <= fact; guy *= prime) {
        out += fact / guy;
    }
    return out;
}

void get_arr_cnt(vector<ll> &cnt, vector<ll> &out) {
    for (ll i = 0; i < num_primes; i++)
    {
        for (ll j = primes[i], pow = 1; j < maxa; j *= primes[i], pow++)
            for (ll k = j; k < maxa; k += j)
                out[i] += cnt[k];
    }
}

bool is_good(ll fact, vector<ll> &nums) {
    for (int i = 0; i < num_primes; i++)
        if (nums[i] > get_cnt(fact, primes[i]))
            return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    get_primes();
    num_primes = primes.size();

    ll k;
    cin >> k;
    vector<ll> a(k);
    ll num2 = 0;
    
    vector<ll> cnt(maxa, 0);
    vector<ll> num_guys(num_primes, 0);
    for (int i = 0; i < k; i++)
    {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for (int i = maxa - 2; i >= 0; i--)
        cnt[i] += cnt[i + 1];
    get_arr_cnt(cnt, num_guys);

    ll val = k*1e7;
    for (ll step = k*1e7; step > 0; step /= 2) {
        while (val - step > 0 && is_good(val - step, num_guys))
            val -= step;
    }
    cout << val << "\n";
}