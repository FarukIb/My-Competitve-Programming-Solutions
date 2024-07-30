#include <bits/stdc++.h>

using namespace std;

void recur(int n, int f, int t, int h, vector<pair<int, int> >& arr) {
    if (n == 0)
        return;
    recur(n - 1, f, h, t, arr);
    arr.push_back(pair<int, int>(f, t));
    recur(n - 1, h, t, f, arr);
}

vector<pair<int, int> > get_moves(int num_stack) {
    vector<pair<int, int> > arr;
    recur(num_stack, 0, 2, 1, arr);
    return arr;
}

void cout_potezi(vector<vector<int> > &stacks) { 
    for (int i = 0; i < 3; i++) 
    {
        cout << i << ": ";
        for (int j : stacks[i])
            cout << j <<" ";
        cout <<"\n";
    }
    cout <<"\n";
}

int main() {
    vector<vector<int> > stacks(3, vector<int>());
    int n;
    cin >> n;
    for (int i = n - 1; i >= 0; i--) {
        stacks[0].push_back(i);
    }

    vector<pair<int, int> > potezi = get_moves(n);

    cout_potezi(stacks);
    for (pair<int, int> potez : potezi) {
        int topp = stacks[potez.first][stacks[potez.first].size() - 1];
        stacks[potez.first].pop_back();
        stacks[potez.second].push_back(topp);

        cout_potezi(stacks);
    }
}
