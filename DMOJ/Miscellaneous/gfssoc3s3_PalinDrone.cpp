// the formula for the number of palindromic numbers with length n is
// (9 * pow(10, (n - 1) / 2) ) -- cool article https://www.geeksforgeeks.org/count-of-n-digit-palindrome-numbers/
// using this formula we can sum up the output of the formula for every number up to (n + 1) to get the answer
// this by itself isn't enough as n can be very large

// notice that when n is larger than 18, the formula will output a number divisible by 1000000000(because of pow(10, (n - 1) / 2))
// so for every n larger than 18 the answer is the same, since the formula will 

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#define ll long long
#define mod 1000000000

using namespace std;

ll getNum(ll x)
{
    return (ll) (9 * pow(10, (x - 1) / 2) );
}

int main()
{
    string nS;
    cin >> nS;

    ll n;
    if (nS.size() >= 17)
        n = (ll)1e18;
    else
        n = stoll(nS);
    
    ll out = 0;
    for (int i = 1; i <= n; i++)
    {
        ll x = getNum(i);
        if (x % mod == 0)
            break;
        out += x;
        out %= mod;
    }

    cout << out << endl;
}