#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int a, b;
    cin >>a >>b;
    string A = bitset<33>(a).to_string();
    string B = bitset<33>(b).to_string();
    int out = 0;
    cout << A << "\n" << B <<"\n";
    for (int i = 0; i <A.size(); i++)
        if ( A[i] == '1')
            out++;
    for (int i = 0; i <B.size(); i++)
        if ( B[i] == '1')
            out++;
    cout << out <<"\n";
}