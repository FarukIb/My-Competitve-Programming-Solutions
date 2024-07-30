#include <bits/stdc++.h>

using namespace std;

string recur(string x) {
    if (x.size() % 2 == 1)
        return x;

    string half1, half2;
    for (int i = 0; i < x.size() / 2; i++)
        half1 += x[i];
    for (int i = x.size() / 2; i < x.size(); i++)
        half2 += x[i];

    half1 = recur(half1);
    half2 = recur(half2);

    if (half1 > half2)
        return half2 + half1;
    return half1 + half2;
}

int main() {
    string a, b;
    cin >> a >> b;
    if (recur(a) == recur(b))
        cout << "YES\n";
    else
        cout << "NO\n";
}