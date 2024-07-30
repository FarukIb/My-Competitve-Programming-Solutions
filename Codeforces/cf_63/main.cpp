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
    int k;
    cin >> k;

    vector<int>arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    map<int, int> guys;
    set<int> singles;
    for (int i = 0; i < k - 1; i++)
        guys[arr[i]]++;
    for (pii t : guys) {
        if (t.second == 1)
            singles.insert(t.first);
    }

    for (int i = 0; i + k - 1 < n; i++) {
        if (i > 0)
        {
            int rem = arr[i - 1];
            guys[rem]--;
            if (guys[rem] == 0)
                singles.erase(rem);
            if (guys[rem] == 1)
                singles.insert(rem);
        }
        int add = arr[i + k - 1];
        guys[add]++;
        if (guys[add] == 1)
            singles.insert(add);
        if (guys[add] == 2)
            singles.erase(add);
        
        if (singles.empty())
            cout << "Nothing\n";
        else  
            cout << *prev(singles.end()) << "\n";
    }
}