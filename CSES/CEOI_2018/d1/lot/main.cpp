#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n, l;
void shift_forward(vector<int> &arr) {
    for (int i = 2 * n - 1; i > 0; i--)
        arr[i] = arr[i - 1];
    arr[0] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> l;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    int q;
    cin >> q;
    vector<int> vals(q);
    for (int Q = 0; Q < q; Q++) {
        cin >> vals[Q];
    }

    vector<vector<int> > mat(q, vector<int>(n, 0));

    vector<int> csum(n + 1, 0);
    vector<int> diff(2 * n, 0);
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i] != arr[j])
                diff[j - i + n]++;
        }
    }
    for (int j = 0; j <= n - l; j++)
        csum[diff[j + n]]++;
    csum[0]--;
    for (int j = 1; j < n; j++)
        csum[j] += csum[j - 1];
        
    for (int j = 0; j < q; j++)
        mat[j][0] = csum[vals[j]];

    for (int i = 1; i <= n - l; i++) {
        for (int j = 0; j < n; j++)
            if (arr[i - 1] != arr[j])
                diff[j + n]--;
        shift_forward(diff);
        for (int j = 0; j < n; j++)
            if (arr[i + l - 1] != arr[j])
                diff[j + 1 - l + n]++;
            

        fill(csum.begin(), csum.end(), 0);
        for (int j = 0; j <= n - l; j++)
            csum[diff[j + n]]++;
        csum[0]--;
        for (int j = 1; j <= l; j++)
            csum[j] += csum[j - 1];
        
        for (int j = 0; j < q; j++)
            mat[j][i] = csum[vals[j]];
    }

    for (int Q = 0; Q < q; Q++) {
        cout << mat[Q][0];
        for (int i = 1; i <= n - l; i++)
            cout <<" " << mat[Q][i];
        cout << "\n";
    }
}

