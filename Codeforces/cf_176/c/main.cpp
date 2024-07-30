#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    int m;
    cin >> m;
    while (m--)
    {
        int idx;
        cin >> idx;
        arr[idx - 1] = -arr[idx - 1];
    }
    stack<int> curr; bool ok = true;
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] < 0 || curr.empty() || curr.top() != arr[i])
        {
            curr.push(abs(arr[i]));
            arr[i] = -abs(arr[i]);
        }
        else if (curr.top() == arr[i])
            curr.pop();
        else    
            ok = false;
    }
    if (!curr.empty())
        ok = false;
    if (ok) {
        cout << "YES\n";
        for (int s : arr)
            cout << s << " ";
        cout << "\n";
    }
    else
        cout << "NO\n";
}