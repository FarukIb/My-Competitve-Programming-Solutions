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
    vector<int>arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    stack<pii> stck;
    stck.push({0, -1});
    for (int i = 0; i < n; i++) {
        while (stck.top().second >= arr[i]) 
            stck.pop();
        cout << stck.top().first << " ";
        stck.push({i + 1, arr[i]});
    }
    cout << endl;
}