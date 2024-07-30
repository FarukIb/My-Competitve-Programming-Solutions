#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct ucenik {
    string ime;
    double prosjek;

    ucenik() {
        ime = "a";
        prosjek = 2.5;
    }

    ucenik(double prosjek_, string ime_) {
        prosjek = prosjek_;
        ime = ime_;
    }

    bool operator<(const ucenik& b) const {
        return prosjek < b.prosjek;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    set<int> faruk{1, 2, 3, 4, 5};
    cout << faruk.count(5) << endl;
    faruk.erase(5);
    cout << faruk.count(5) << endl;

    for (int x : faruk) {
        cout << x << endl;
    }
}