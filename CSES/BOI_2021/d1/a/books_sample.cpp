#include <bits/stdc++.h>

#include "books.h"

using namespace std;
//
// --- Sample implementation for the task books ---
//
// To compile this program with the sample grader, place:
//     books.h books_sample.cpp sample_grader.cpp
// in a single folder and run:
//     g++ books_sample.cpp sample_grader.cpp
// in this folder.
//

int get(int idx, vector<int> &arr) {
    if (arr[idx] == -1)
        arr[idx] = skim(idx + 1);
    return arr[idx];
}

void solve(int N, int K, long long A, int S) {
    int n = N;
    vector<int> arr;
    arr.resize(n, -1);
    int k = K;
    int a = A;
    int s = S;

    int frst = n;
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (r + l) / 2;
        if (get(mid, arr) < a - 1)
            l = mid + 1;
        else
            r = mid;
    }
    if (get(l, arr) >= a - 1)
        frst = l;
    
    int sum = 0;
    for (int i = 0; i < k - 1; i++)
        sum += get(i, arr);
    
    if (sum + get(l, arr) >= a && sum + get(l, arr) <= 2 * a) {
        vector<int> arr;
        for (int i = 1; i <= k - 1; i++)
            arr.push_back(i);
        arr.push_back(l + 1);
        answer(arr);
        return;
    }

    if (frst <=k) {
        impossible();
        return;
    }

    l = 0, r = frst - k;
    while (l < r) {
        int mid = (r + l) / 2;
        sum = 0;
        for (int i = mid; i < mid + k; i++)
            sum += get(i, arr);
        if (sum < A)
            l = mid + 1;
        else
            r = mid;
    }

    sum = 0;
    vector<int> ar;
    for (int i = l; i < l + k; i++)
        ar.push_back(i + 1), sum += get(i, arr);
    
    if (sum < a || sum > 2 * a)
    {
        impossible();
        return;
    }
    answer(ar);
}
