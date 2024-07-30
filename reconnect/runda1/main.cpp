#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;

    vector<int> nums;
    for (char x :  s)
        if (x >= '0' && x <= '9')
            nums.push_back(x - '0');

    sort(nums.begin(), nums.end());
    for (int i = nums.size() - 1; i >= 0; i--)
        cout << nums[i];
    cout << endl;
}   