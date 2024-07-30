#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
    TrieNode* on;
    TrieNode* off;

    TrieNode() { on = nullptr, off = nullptr; }
};

TrieNode* root = new TrieNode();

void add(int x) {
    TrieNode* curr = root;
    for (int bit = 20; bit >= 0; bit--) {
        if (x & (1 << bit)) {
            if (curr->on != nullptr)
                curr = curr-> on;
            else
                curr->on = new TrieNode(), curr = curr -> on;
        }
        else {
            if (curr->off != nullptr)
                curr = curr->off;
            else
                curr->off = new TrieNode(), curr = curr -> off;
        }
    }
}

int findIt(int x) {
    TrieNode* curr = root;

    int out = 0;
    for (int bit = 20; bit >= 0; bit--) {
        int desiredBit = 0;
        if (x & (1 << bit))
            desiredBit = 1;

        if (desiredBit == 0) {
            if (curr->off != nullptr)
                curr = curr->off;
            else
                curr = curr->on, out += 1 << bit;
        }
        else {
            if (curr->on != nullptr)
                curr = curr->on;
            else
                curr = curr->off, out += 1 << bit;
        }
    }

    return out;
}

int main() {
    int n, m;
    cin >> n >> m;

    set<int> notIn;
    for (int i = 0; i <= 1 << 20 - 1; i++)
        notIn.insert(i);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        notIn.erase(x);
    }

    for (int x : notIn)
        add(x);

    int prev = 0;
    while (m--) {
        int x;
        cin >> x;
        x = prev ^ x;
        prev = x;

        cout << findIt(x) << "\n";
    }
}