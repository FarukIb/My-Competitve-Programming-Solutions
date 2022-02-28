# 1555 - Garland
 I did not solve this one on my own but here is the approach that I found out after reading up a bit.
 
 If we have that:
 
 $a_2=\dfrac{a_1}{2} + \dfrac{a_3}{2} - 1$
 $\dfrac{a_1}{2} = a_2 - \dfrac{a_3}{2} + 1$
 $a_1=2a_2-a_3+2$
 
 We can now binary search over $a_2$ and find $a_n$ from the final $a_2$. So why can we binary search over $a_2$? Well if we were to visualise it, it makes sense that the higher we put the second lantern the higher the lowest lantern will be.
 
 ###### NOTE: -0.00 is a thing so always so $cout << abs((ld)val);$
 
 ```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int n;
bool check(ld h1, ld h2) {
    ld h = 0;
    for (int i = 2; i < n; i++)
    {
        h = 2 * h2 - h1 + 2;
        if (h < 0)
            return false;
        h1 = h2;
        h2 = h;
    }
    return true;
}

ld out(ld h1, ld h2) {
    ld h = 0;
    ld outt = 1e15;
    for (int i = 2; i < n; i++)
    {
        h = 2 * h2 - h1 + 2;
        h1 = h2;
        h2 = h;
    }
    return h;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ld a;
    while (cin >> n >> a) {
        ld l = 0, r = a;
        while (r - l > 1e-15) {
            ld mid = (r + l) / 2;
            if (check(a, mid))
                r = mid;
            else
                l = mid;
        }
        cout << fixed << setprecision(2) << abs(out(a, l)) << "\n";
    }
}

```
 
 ## Tags
 #math #binary_search
