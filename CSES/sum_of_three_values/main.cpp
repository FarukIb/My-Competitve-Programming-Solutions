#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

vector<ll> arr;
void out(int a, int b, int c) {
    vector<int> o = {a, b, c};
    sort(all(o));
    a = o[0], b = o[1], c = o[2];
    int A, B, C;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == a)
        {
            A = i;
            break;
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == b and i != A)
        {
            B = i;
            break;
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == c and i != A and i != B) {
            C = i;
            break;
        }
    }
    cout << A + 1 << " " << B + 1 << " " << C + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, x;
    cin >> n >> x;
    unordered_map<ll, ll, custom_hash> here;
    ll a = -1, b, c;
    arr = vector<ll>(n);
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
        here[arr[i]]++;
    }
    vector<ll> arr_r = arr;
    sort(all(arr));

    for (int i = 0; i < n and a == -1; i++) {
        if (arr[i] + arr[n - 1] + arr[n - 2] < x)
            continue;
        for (int j = i + 1; j < n and a == -1; j++) {
            ll needed = x - arr[i] - arr[j];
            if (needed < 0)
                break;
            int O = 0;
            if (needed == arr[i])
                O++;
            if (needed == arr[j])
                O++;
            if (here[needed] > O) {
                a = arr[i];
                b = arr[j];
                c = needed;
            }
        }
    }

    arr = arr_r;

    if (a == -1)
        cout << "IMPOSSIBLE\n";
    else {
        out(a, b, c);
    }
}