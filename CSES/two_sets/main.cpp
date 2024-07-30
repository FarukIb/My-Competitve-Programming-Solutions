#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void print_set(set<int> a) {
    cout << a.size() << endl;
    for (int b : a)
        cout <<b <<" ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    ll sum = n*(n + 1) / 2;
    if (sum % 2) {
        cout << "NO" << endl;
        return 0;
    }
    set<int> set1;
    set<int> set2;
    for (int i = 0; i < n; i++)
        set1.insert(i + 1);
    ll c = 0;
    for (int i = n; i >= 1; i--) {
        if (i + c <= sum / 2)
        {
            c += i;
            set2.insert(i);
            set1.erase(i);
        }
    }

    cout << "YES" << endl;
    print_set(set1);
    print_set(set2);
}