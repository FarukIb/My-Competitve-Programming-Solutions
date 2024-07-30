#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

vector<int> niz;
vector<int> niz2;
vector<int> sorted;

vector<int> my_merge(vector<int> niz, vector<int> niz2) {
    int n = niz.size();
    int m = niz2.size();

    vector<int> sorted;

    int pnt1 = 0, pnt2 = 0;
    while (pnt1 < n && pnt2 < m) {
        if (niz[pnt1] < niz2[pnt2])
        {
            sorted.push_back(niz[pnt1]);
            pnt1++;
        }
        else {
            sorted.push_back(niz2[pnt2]);
            pnt2++;
        }
    } 
    for (; pnt2 < m; pnt2++)
        sorted.push_back(niz2[pnt2]);
    for (; pnt1 < n; pnt1++)
        sorted.push_back(niz[pnt1]);

    return sorted;
}

int main() {

    // N JE STEPEN DVICE
    int n;
    cin >> n;

    niz.resize(n);
    for (int i = 0; i < n; i++)
        cin >> niz[i];

    vector<int> novi;
    for (int vel = 1; vel <= n / 2; vel *= 2) {
        for (int i = 0; i < n; i += vel * 2) {
            vector<int> prva_polovina;
            vector<int> druga_polovina;
            for (int j = i; j < i + vel; j++)
                prva_polovina.push_back(niz[j]);
            for (int j = i + vel; j < i + vel * 2; j++)
                druga_polovina.push_back(niz[j]);
            
            vector<int> merged = my_merge(prva_polovina, druga_polovina);
            for (int j = i; j < i + vel * 2; j++)
                niz[j] = merged[j - i];
        }
    }

    for (int i = 0; i < n; i++)
        cout << niz[i] << endl;
}