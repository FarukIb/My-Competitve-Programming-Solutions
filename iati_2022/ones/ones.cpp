#include <bits/stdc++.h>
#include "ones.h"
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
const int needed = 9;

vector<bool> rand_shuffle() {
    vector<bool> arr(n);
    for (int i = 0; i < n; i++)
            if (rand() % 2)
                arr[i] = 1;
    return arr;
}

vector<bool> set_shuffle(int num) {
    vector<bool> arr(n);
    for (int i = 0; i < needed + 1; i++)
        if ((1 << i) & num)
            arr[i] = 1;
    return arr;
}

pair<int, int> find_longest_subarray_of_ones(int n) {
    srand(time(0));
    ::n = n;
    if (n <= needed + 1) {
        for (int mask = 1; mask < (1 << n); mask++) {
            int me = mask ^ (mask - 1);
            if (flip_bits(set_shuffle(me)) == n)
                return pii(0, n - 1);
        }
        flip_bits(set_shuffle((1 << n) - 1));
        return pii(0, n - 1);
    }

    while (flip_bits(rand_shuffle()) > needed)
        continue;
    int max_mask = 0, val = flip_bits(set_shuffle(0));
    for (int mask = 1; mask < (1 << (needed + 1)); mask++) {
        int me = mask ^ (mask - 1);
        int oo =flip_bits(set_shuffle(me));
        if (oo > val)
            max_mask = mask, val = oo;
    }
    flip_bits(set_shuffle((1 << (needed + 1)) - 1));
    flip_bits(set_shuffle(max_mask));
    return pii(0, val - 1);
}