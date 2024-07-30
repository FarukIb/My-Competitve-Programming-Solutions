#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double
#define matrix vector<vector<long long> >
#define mod (1000000007)

using namespace std;

matrix get_base_matrix(int c) {
    matrix mat(c, vector<ll>(c, 0));

    for (int i = 0; i < c; i++)
        mat[i][c - 1] = 1;
    for (int i = 0; i < c - 1; i++)
        mat[i + 1][i] = 1;
    
    return mat;
}

matrix multip(matrix &a, matrix &b) {
    matrix mat(a.size(), vector<ll>(a.size(), 0));

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            for (int k = 0; k < a.size(); k++)
                mat[i][j] += (a[i][k] * b[k][j]) % mod, mat[i][j] %= mod;
        }
    }

    return mat;
}

matrix base_mat;
matrix expo(ll exp) {
    if (exp == 1)
        return base_mat;
    matrix half = expo(exp / 2);
    half = multip(half, half);
    if (exp & 1 == 1) {
        half = multip(base_mat, half);
    }
    return half;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, c;
    cin >> n >> c;

    base_mat = get_base_matrix(c + 1);
    matrix mat = expo(n + 2);

    cout << mat[0][c] << "\n";
}
