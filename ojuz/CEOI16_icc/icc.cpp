// 90 pts
#include "icc.h"
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
 
using namespace std;
 
typedef pair<int, int> pii;

vector<vector<int> > components;

bool query(vector<int> a, vector<int> b) {
    int a_niz[a.size()], b_niz[b.size()];
    for (int i = 0; i < a.size(); i++)
        a_niz[i] = a[i];
    for (int i = 0; i < b.size(); i++)
        b_niz[i] = b[i];
    return query(a.size(), b.size(), a_niz, b_niz);
}

void merge_components(int A, int B) {
    int a, b;
    for (int i = 0; i < components.size(); i++)
    {
        if (count(all(components[i]), A))
            a = i;
        if (count(all(components[i]), B))
            b = i;
    }
    if (a > b)
        swap(a, b);
    vector<int> neww_component = components[a];
    neww_component.insert(neww_component.end(), all(components[b]));
    components.erase(components.begin() + b);
    components.erase(components.begin() + a);
    components.push_back(neww_component);
}

vector<int> expand_component_array(vector<int> me) {
    vector<int> neww;
    for (int i : me)
        neww.insert(neww.end(), all(components[i]));
    return neww;
}

bool components_query(vector<int> a, vector<int> b) {
    vector<int> newa = expand_component_array(a), newb = expand_component_array(b);
    return query(newa, newb);
}

pii find_edge_from_true_query(vector<int> a, vector<int> b) {
    pii out;
    int l = 0, r = a.size();
    while (l < r) {
        int mid = (l + r) / 2;
        if (query(vector<int>(a.begin(), a.begin() + mid + 1), b))
            r = mid, out.first = mid;
        else
            l = mid + 1;
    }

    l = 0, r = b.size();
    while (l < r) {
        int mid = (l + r) / 2;
        if (query(a, vector<int>(b.begin(), b.begin() + mid + 1)))
            r = mid, out.second = mid;
        else
            l = mid + 1;
    }
    return pii(a[out.first], b[out.second]);
}

void run(int n) {
    for (int i = 1; i <= n; i++)
        components.push_back(vector<int>(1, i));
    
    for (int i = 0; i < n - 1; i++) {
        int max_bit = __lg(n - i) + 1;
        vector<int> bits(max_bit);
        iota(all(bits), 0);
        random_shuffle(all(bits));

        vector<int> find_a, find_b;
        for (int bit : bits)
        {
            vector<int> cmp1, cmp2;
            for (int i = 0; i < components.size(); i++)
            {
                if (i & (1 << bit))
                    cmp1.push_back(i);
                else
                    cmp2.push_back(i);
            }
            if (components_query(cmp1, cmp2)) {
                find_a = expand_component_array(cmp1), find_b = expand_component_array(cmp2);
                break;
            }
        }
        pii edge = find_edge_from_true_query(find_a, find_b);
        setRoad(edge.first, edge.second);
        merge_components(edge.first, edge.second);
    }
}