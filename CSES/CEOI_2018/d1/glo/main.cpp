#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
int lis(vector<int> &a) {
    const int INF = 2e9 + 1000;
    vector<int> d(n+1, INF);
    d[0] = -INF;
 
    for (int i = 0; i < n; i++) {
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j-1] < a[i] && a[i] < d[j])
            d[j] = a[i];
    }
 
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (d[i] < INF)
            ans = i;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int x;
    cin >> n >> x;
    if (x == 1e9) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >>arr[i];

        const int INF = 2e9 + 1000;    
        vector<int> arr2 = arr;
        reverse(arr2.begin(), arr2.end());
        for (int i = 0; i < n; i++)
            arr2[i] = -arr2[i];
        vector<int> d2(n + 1, INF);
        d2[0] = -INF;

        int curr = 0;
        vector<int> right(n + 1);
        right[0] = 0;
        for (int i = 0; i < n; i++) {
            int j = upper_bound(d2.begin(), d2.end(), arr2[i]) - d2.begin();
            if (d2[j - 1] < arr2[i] && arr2[i] < d2[j])
            {
                if (j > curr)
                    curr = j;
                d2[j] = arr2[i];
            }
            right[n - i - 1] = curr;
        }

        vector<int> d1(n+1, INF);
        d1[0] = -INF;

        curr = 0;
        int ans = right[n];
        for (int i = 0; i < n; i++) {
            int j = upper_bound(d1.begin(), d1.end(), arr[i]) - d1.begin();
            if (d1[j - 1] < arr[i] && arr[i] < d1[j])
            {
                d1[j] = arr[i];
                if (j > curr)
                    curr = j;
            }
            ans = max(ans, right[i + 1] + curr);
        }

        cout << ans << endl;
        }
        else {
            vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >>arr[i];
        
        if (x == 0)
        {
            cout << lis(arr) << endl;
            return 0;
        }
    
        int ans = lis(arr);
        for (int r = 1; r < n; r++) {
            for (int i = r; i < n; i++)
                arr[i] += x;
    
            ans = max(ans, lis(arr));
            for (int i = r; i < n; i++)
                arr[i] -= x;
        }
    
        cout << ans << endl;
    }
}