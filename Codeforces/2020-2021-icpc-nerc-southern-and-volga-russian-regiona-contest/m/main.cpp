#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int D = 400;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<bool> big(n);
        vector<int> idxs;
        vector<vector<int> > big_sets;
        vector<vector<int> > sets(n);
        vector<int> al;

        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            sets[i] = vector<int>(k);
            for (int j = 0; j < k; j++) {
                cin >> sets[i][j];
                al.push_back(sets[i][j]);
            }
            sort(all(sets[i]));
            if (k > D)
            {
                big[i] = true;
                idxs.push_back(i);
                big_sets.push_back(sets[i]);
            }
        }
        sort(all(al));
        al.erase(unique(al.begin(), al.end()), al.end());
        map<int, int> trans;
        for (int i = 0; i < al.size(); i++)
            trans[al[i]] = i;
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < sets[i].size(); j++)
                sets[i][j] =trans[sets[i][j]];
        for (int i = 0; i < big_sets.size(); i++)
            for (int j = 0; j < big_sets[i].size(); j++)
                big_sets[i][j] = trans[big_sets[i][j]];
        // checking big_sets;
        bool found = false;
        int a, b;

        vector<int> here(al.size());
        for (int i = 0; i < big_sets.size(); i++) {
            for (int a : big_sets[i])
                here[a]++;
            
            for (int j = 0; j < n; j++)  {
                if (j == idxs[i])
                    continue;
                int common = 0;
                for (int k = 0; k < sets[j].size(); k++) {
                    here[sets[j][k]]++;
                    if (here[sets[j][k]] >= 2)
                        common++;
                }
                if (common >= 2)
                {
                    found = true;
                    a = idxs[i], b = j;
                    break;
                }
                for (int k = 0; k < sets[j].size(); k++)
                    here[sets[j][k]]--;
            }
            if (found)
                break;
            for (int a : big_sets[i])
                here[a]--;
        }

        if (found) {
            cout << a + 1 << " " << b + 1 << "\n";
            continue;
        }

        vector<vector<pii> > cool_arr(al.size());
        for (int i = 0; i < n; i++) {
            if (big[i])
                continue;
            for (int j = 0; j < sets[i].size(); j++)
                for (int k = j + 1; k < sets[i].size(); k++)
                    cool_arr[sets[i][j]].push_back({sets[i][k], i});
        }
        fill(all(here), -1);
        for (int i = 0; i < al.size(); i++) {
            for (int j = 0; j < cool_arr[i].size(); j++)
            {
                if (here[cool_arr[i][j].first] != -1) {
                    found = true;
                    a = cool_arr[i][j].second;
                    b = here[cool_arr[i][j].first];
                    break;
                }
                here[cool_arr[i][j].first] = cool_arr[i][j].second;
            }
            if (found)
                break;
            for (int j = 0; j < cool_arr[i].size(); j++)
                here[cool_arr[i][j].first] = -1;
        }

        if (found) {
            cout << a + 1 << " " << b + 1 << "\n";
        } else {
            cout << "-1\n";
        }
    }
}