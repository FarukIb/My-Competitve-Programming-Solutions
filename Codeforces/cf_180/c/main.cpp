#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pii> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first; arr[i].second = i;
    }
    int f = n / 3 + ((n % 3) > 0 ? 1 : 0), s = (n / 3) * 2 + ((n % 3) > 1 ? 2 : 0);
    sort(all(arr));
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < f; i++)
        a[arr[i].second] = i, b[arr[i].second] = arr[i].first - i;
    for (int i = f; i < s; i++)
        b[arr[i].second] = i, a[arr[i].second] = arr[i].first - i;
    
    for (int i = s; i < n; i++)    
        b[arr[i].second] = n - i - 1, a[arr[i].second] = arr[i].first - (n - i - 1);
    
    cout << "YES\n";
    for (int i = 0; i < n; i++)
        cout << a[i] <<" ";
    cout << "\n";
    for (int i = 0; i < n; i++)
        cout << b[i] <<" ";
    cout << "\n";
}