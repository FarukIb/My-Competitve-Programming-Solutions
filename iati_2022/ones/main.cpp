#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e4;

int get_run(vector<int> &arr) {
    int last = 0;
    int maxi = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] == 0) {
            maxi = max(maxi, i - last);
            last = i + 1;
        }
    }
    maxi = max(maxi, N - last);
    return maxi;
}

int get_idx_of_first(vector<int> &arr, int len) {
    int last = 0;
    int maxi = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] == 0) {
            maxi = max(maxi, i - last);
            if (i - last >= len - 1)
                return last;
            last = i + 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(0));


    int needed = 9;
    vector<int> arr(N);
    int cnt = 0, l= 0;
    int num_shuffle = 10000;
    double avg = 0;
    for (int t = 0; t < num_shuffle; t++) {
        for (int i = 0; i < N; i++) {
            if (rand() % 2)
                arr[i] ^= 1;
        }
        if (get_run(arr) <= needed)
        {
            //cout << t + 1 - l << endl;
            avg += get_idx_of_first(arr, get_run(arr));
            l = t;
            cnt++;
        }
    }
    cout << " avg : " << avg / (double) cnt;
}