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
    cin>>n;
    vector<int> arr(n+2);
    arr[0] = 0;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    arr[n + 1]=0;
    
    int sum=0;

    for(int i = 1; i <= n; i++)
    {
        if (arr[i - 1] > 0)
        {
            arr[i - 1]--;
        }
        else if(arr[i] == 0 && arr[i + 1] > 0)
        {
            arr[i + 1]--;
        }
        else {
            sum++;
        }
    }

    cout << sum << "\n";
}