#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        string s;
        for (int i = 1; i < n; i++) {
            if (arr[i] > arr[i - 1])
                s += 'G';
            else if (arr[i] == arr[i - 1])
                s += 'E';
            else
                s += 'L';
        }

        string str;
        cin >> str;
        int m = str.size();

        str += '$';
        str += s;

        vector<int> z(str.size(), 0);
        int l = 0, r = 0;
        for (int i = 1; i < str.size(); i++) {
            if (i > r) {
                l = i, r = i;
                while (str[r] == str[r - i] && r < str.size())
                    r++;
                z[i] = r - l;
                r--;
            }
            else {
                int k = i - l;

                int rem = r - i + 1;
                if (z[k] < rem)
                    z[i] = z[k];
                else {
                    l = i;
                    while (str[r] == str[r - i] && r < str.size())
                        r++;
                    z[i] = r - l;
                    r--;
                }
            }
        }

        bool ok = false;
        for (int i = 0; i < str.size(); i++)
            if (z[i] == m)
                ok = true;
        if (ok)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";
    }
}