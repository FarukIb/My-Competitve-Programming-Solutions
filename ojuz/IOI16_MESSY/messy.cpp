#include <bits/stdc++.h>

using namespace std;

#include "messy.h"

int N;

void add_elements(int l, int r) {
    if (l + 1 == r)
        return;
    string my_string(N, '1');
    int mid = (l + r) / 2;
    for (int i = l; i < r; i++)
        my_string[i] = '0';
    for (int i = l; i < mid; i++) {
        my_string[i] = '1';
        add_element(my_string);
        my_string[i] = '0';
    }
    add_elements(l, mid);
    add_elements(mid, r);
}

vector<int> perm;

void ask(int l, int r, vector<int> my_idxs) {
    if (l == r) {
        perm[my_idxs[0]] = l;
        return;
    }
    string ask_base(N, '1');
    for (int i : my_idxs)
        ask_base[i] = '0';
    
    vector<int> half_idxs;
    vector<int> other_half;
    for (int i = 0; i < my_idxs.size(); i++)
    {
        ask_base[my_idxs[i]] = '1';
        bool here = check_element(ask_base);
        ask_base[my_idxs[i]] = '0';

        if (here)
            half_idxs.push_back(my_idxs[i]);
        else
            other_half.push_back(my_idxs[i]);
    }
    int mid = (l + r) / 2;
    ask(l, mid, half_idxs);
    ask(mid + 1, r, other_half);
}

std::vector<int> restore_permutation(int n, int w, int r) {
    N = n;
    add_elements(0, n);
    compile_set();
    vector<int> all_idxs(N);
    for (int i = 0; i < N; i++)
        all_idxs[i] = i;
    perm.resize(n);
    ask(0, n - 1, all_idxs);
    return perm;
}
