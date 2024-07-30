#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >>x[i] >> y[i];
    if (n <= 2)
        cout << "-1\n";
    else if (n == 3)
    {
        ll max_x = *max_element(all(x)), max_y = *max_element(all(y));
        ll min_y = *min_element(all(y)), min_x = *min_element(all(x));
        ll area = (max_x - min_x) * (max_y - min_y);
        if (area == 0)
            cout << "-1\n";
        else
            cout << area << "\n";
    }
    else
        cout << "1\n";
}