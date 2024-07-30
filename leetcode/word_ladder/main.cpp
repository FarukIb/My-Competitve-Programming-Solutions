#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool can_move(string &a, string &b) {
        int num_diff = 0;
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                num_diff++;
        if (num_diff == 1)
            return true;
        return false;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int b_idx = -1, e_idx = -1, n = wordList.size();
        for (int i = 0; i < n; i++) {
            if (wordList[i] == endWord)
                e_idx = i;
        }
        if (e_idx == -1)
            return 0;

        wordList.push_back(beginWord);n++; b_idx = n - 1;
        vector<vector<int> > adj(n);

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++) {
                if (can_move(wordList[i], wordList[j]))
                {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        queue<int>q;
        q.push(b_idx);
        vector<bool> visited(n, false); visited[b_idx] = true;
        vector<int> dist(n, 0);
        dist[b_idx] = 1;
        while (!q.empty()) {
            int c = q.front();
            q.pop();
            for (int x : adj[c]) {
                if (!visited[x]) {
                    q.push(x);
                    visited[x] = true;
                    dist[x] = dist[c] + 1;
                }
            }
        }

        if (e_idx == -1)
            return 0;
        return dist[e_idx];
    }
};

int main(){
    string a = "hit", b = "cog";
    vector<string> wl = {"hot","dot","dog","lot","log","cog"};
    Solution sol;
    cout << sol.ladderLength(a, b, wl) << "\n";
}