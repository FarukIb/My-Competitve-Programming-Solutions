#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

int n;
pii elem[200005];

int main()
{
    int n, l, u;
    cin >> n >> l >> u;

    vector<pii> arr(n);

    for (size_t i = 0; i < n; i++)
    {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr.begin(), arr.end());
    
    vector<int> out;
    ll sum = 0; size_t r = 0;
    for (int lo = 0; lo < n; lo++)
    {
        while (sum < l && r < n)
            sum += arr[r].first, r++;
        if (sum >= l && sum <= u)
        {
            for (int i = lo; i < r; i++)
                out.push_back(arr[i].second);
            sort(out.begin(), out.end());
            break;
        }
        sum -= arr[lo].first;
    }

    if (out.empty())
    {
        cout << 0 << endl;
        return 0;
    }

    size_t _size = out.size();
    cout << _size << endl;
    for (size_t i = 0; i < _size - 1; i++)
        cout << out[i] << " ";
    cout << out[_size - 1] << endl;

    return 0;
}