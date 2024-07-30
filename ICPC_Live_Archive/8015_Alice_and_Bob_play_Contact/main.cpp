#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
    map<char, TrieNode*> chillun;
    int numPass;

    TrieNode() { numPass = 0; }
};
TrieNode* root;

void add(string s) {
    TrieNode* curr = root;
    curr->numPass++;

    for (int i = 0; i < s.size(); i++) {
        if (curr->chillun.find(s[i]) == curr->chillun.end())
            curr->chillun[s[i]] = new TrieNode();
        curr = curr->chillun[s[i]];
        curr->numPass++;
    }
}

int maxDpth = 0;
void count(string s, int i, int mini, TrieNode* curr) {
    maxDpth = i;
    if (mini == 0)
        return;
    if (i == s.size() || curr->chillun.find(s[i]) == curr->chillun.end())
        return;
    count(s, i + 1, min(mini - 1, curr->chillun[s[i]]->numPass - 1), curr->chillun[s[i]]);
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        queue<string> queries;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            queries.push(s);
        }

        root = new TrieNode();
        for (int i = 0; i < m; i++) {
            string s;
            cin >> s;
            add(s);
        }

        int out = 0;
        while (!queries.empty()) {
            string curr = queries.front();
            queries.pop();

            maxDpth = 0;
            count(curr, 0, root->numPass, root);
            out += maxDpth;
        }

        cout << out << "\n";
    }
}