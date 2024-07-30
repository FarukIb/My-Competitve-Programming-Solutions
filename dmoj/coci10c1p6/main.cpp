#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
void swap_guy(int val, vector<int> &arr) {
    int curr_idx = find(all(arr), val) - arr.begin();
    int next_idx = (curr_idx + 1) % n;
    if (next_idx != 0)
        swap(arr[curr_idx], arr[next_idx]);
    else {
        arr.pop_back();
        arr.insert(arr.begin() + 1, val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    vector<int> arr1(n), arr2(n);
    for (int i = 0; i < n; i++)
        cin >> arr1[i];
    for (int i = 0; i < n; i++)
        cin >> arr2[i];
    vector<int> seq;
    for (int i = 1; i < n; i++) {
        while (arr1[i] != arr2[i])
        {
            swap_guy(arr1[i], arr2);
            cout << arr1[i] << "\n";
        }
    }
}