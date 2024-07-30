//#include "icc.h"
#include "icc.cpp"
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void setRoad(int a, int b) {
    cout << "ans: " << a << " " << b << "\n";
}

int query(int size_a, int size_b, int a[], int b[]) {
    for (int i = 0; i < size_a; i++)
        cout << a[i] << " ";
    cout << "\n";
    for (int i = 0; i < size_b; i++)
        cout << b[i] << " ";
    cout << "\n";
    cout << "::::::::::\n";

    int out;
    cin >> out;
    return out;
}

int main() {
    run(5);
}