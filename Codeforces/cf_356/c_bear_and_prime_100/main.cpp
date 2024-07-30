#include <bits/stdc++.h>

using namespace std;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

int main() {
    int num = 0;
    for (int x : primes) {
        cout << x << endl;
        string ans; cin >> ans;
        if (ans == "yes")
            num++;
    }

    if (num > 1)
        cout << "composite" << endl;
    else if (num == 0)
        cout << "prime" << endl;
    else
    {
        num = 0;
        for (int x : primes) {
            if (x * x > 100)    
                break;
            cout << x * x << endl;
            string ans; cin >> ans;
            if (ans == "yes")
                num++;
        }

        if (num == 0)
            cout << "prime" << endl;
        else
            cout << "composite" << endl;
    }
}