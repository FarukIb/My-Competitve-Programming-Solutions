#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int> > permutations;

void dfs(vector<int> curr, int left, int n)
{
    if (curr.size() == n)
    {
        permutations.push_back(curr);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!(left & (1 << i)))
        {
            int newLeft = left;
            newLeft |= 1 << i;

            vector<int> newCurr = curr;
            newCurr.push_back(i);

            dfs(newCurr, newLeft, n);
        }
    }
}

void getPerms(int n)
{
    permutations.clear();
    dfs({}, 0, n);
}

int mat[10][10];
int main()
{
    int T, n;
    cin >> T;
    while (T--)
    {
        cin >> n;
        getPerms(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> mat[i][j];

        int minSum = (int)1e9;
        for (vector<int> perm : permutations)
        {
            int currSum = 0;
            for (int i = 0; i< n; i++)
                currSum += mat[i][perm[i]];
            minSum = min(minSum, currSum);
        }

        cout << minSum << endl;
    }

    return 0;
}
