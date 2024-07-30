#include "scales.h"
#include <bits/stdc++.h> 

using namespace std;

int W[6];
void init(int T) {

}

void orderCoins() {
    // first;
    vector<int> f(3);
    set<int> left;
    left.insert(1);
    left.insert(2);
    left.insert(3);

    f[0] = getLightest(1, 2, 3);
    left.erase(f[0]);
    f[1] = getMedian(1, 2, 3);
    left.erase(f[1]);
    for (int x : left)
        f[2] = x;
    left.clear();
    
    // second
    vector<int> l(3);
    left.insert(4);
    left.insert(5);
    left.insert(6);

    l[0] = getLightest(4, 5, 6);
    left.erase(l[0]);
    l[1] = getMedian(4, 5, 6);
    left.erase(l[1]);
    for (int x : left)
        l[2] = x;
    left.clear();

    int pnt1 = 0, pnt2 = 0;
    while (pnt1 < 3 && pnt2 < 3) {
        if (pnt1 != 2) {
            int mini = getLightest(f[pnt1], l[pnt2], f[pnt1 + 1]);
            W[pnt1 + pnt2] = mini;
            if (mini == f[pnt1])
                pnt1++;
            else
                pnt2++;
        }
        else if (pnt2 != 2) {
            int mini = getLightest(f[pnt1], l[pnt2], l[pnt2 + 1]);
            W[pnt1 + pnt2] = mini;
            if (mini == f[pnt1])
                pnt1++;
            else
                pnt2++;
        } else {
            int maxi = getHeaviest(f[2], l[2], f[1]);
            W[5] = maxi;
            if (maxi == f[2])
                W[4] = l[2];
            else
                W[4] = f[2];
            pnt1++, pnt2++;
        }
    }
    while (pnt1 < 3)
        W[pnt1 + 3] = f[pnt1], pnt1++;
    while (pnt2 < 3)
        W[pnt2 + 3] = l[pnt2], pnt2++;

    answer(W);
}

/*
5 2 6 3 1 4 
5 3 1 2 4 6 
1 2 4 6 5 3 
4 3 6 5 5 1 
3 5 6 1 2 4 
6 5 3 2 4 1 
1 3 4 5 6 2 
6 1 4 3 5 2 

5 2 6 3 1 4 6
5 3 1 2 4 6 6
1 2 4 6 5 3 6
4 3 6 5 1 2 6
3 5 6 1 2 4 6
6 5 3 2 4 1 6
1 3 4 5 6 2 6
6 1 4 3 5 2 6
4 2 6 1 5 3 6
1 2 6 4 3 5 6
2 1 6 5 4 3 6
4 1 3 6 5 2 6
3 4 5 1 2 6 6
1 2 6 5 3 4 6
4 1 2 6 5 3 6
5 2 3 4 1 6 6
2 5 3 4 1 6 6
6 5 4 3 1 2 6








*/