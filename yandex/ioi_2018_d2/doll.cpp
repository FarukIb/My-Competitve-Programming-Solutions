#include "doll.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> X, Y, C;
struct trigger {
    int id;
    int type;

    trigger() {}
    trigger(int typ)  {
        if (typ != 0) {
            id = typ;
            type = 1;
        } else {
            X.push_back(-1);
            Y.push_back(-1);
            id = X.size();
            type = 0;
        }
    }

    void connect_parent(int par) {
        C[par] = -id;
    }

    void connect_X(trigger x) {
        if (x.type == 0)
            X[id - 1] = -x.id;
        else
            X[id - 1] = x.id;
    }

    void connect_Y(trigger y) {
        if (y.type == 0) 
            Y[id - 1] = -y.id;
        else
            Y[id - 1] = y.id;
    }
};

void recur(trigger curr, int to_make, int depth, int idx, vector<int> &neww_idxs) {
    if (interval_size == 2) {
        int x_idx = idx, y_idx = (1 + (1 << depth));
    }
}

void create_device(int node, trigger root, vector<trigger> targets) {
    int siz = 2, needed = 2, sizp = 1;
    while (siz < targets.size())
        siz *= 2, needed += siz, sizp++;

    vector<int> idxs(siz);
    for (int pow2 = 0; pow2 < sizp; pow2++) {
        int val = (1 << pow2), interval_length = (1 << (sizp - pow2 - 1));
        for (int beg = interval_length; beg < siz; beg += 2*interval_length)
            for (int j = 0; j < interval_length; j++)
                idxs[beg + j] += val;
    }
    vector<bool> skipped(siz);
    vector<int>decarr(siz);
    vector<int> neww_idxs(siz);
    for (int i = 0; i < siz - targets.size(); i++)
        skipped[idxs[i]] = true, decarr[idxs[i]]++;
    int to_skip = 0;
    for (int i = 0; i < siz; i++) {
        to_skip += decarr[i];
        neww_idxs[i] = i - to_skip;
    }
}

void create_circuit(int M, std::vector<int> A) {
    int N = A.size();
    C.resize(M+1);
    vector<trigger> targets;
    for (int i : A)
        targets.push_back(trigger(i));
    trigger zer;
    zer.type = 1, zer.id = 0;
    targets.push_back(zer);
    
    C[0] = -1;
    trigger rootdevice(0);
    for (int i = 1; i <= M; i++)
        C[i] = -rootdevice.id;
    create_device(0, rootdevice, targets);



    answer(C, X, Y);
}
