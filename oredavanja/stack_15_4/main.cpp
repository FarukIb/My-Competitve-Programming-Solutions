#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    deque<int> deq;
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n;i++)
        cin >> arr[i];
    
    for (int i = 0; i < n; i++) {
        while (!deq.empty() and deq.back() <= arr[i])
            deq.pop_back();
        
        if (deq.empty())
            cout << "-1 ";
        else
            cout << deq.back() << " ";
        deq.push_back(arr[i]);
    }
}p