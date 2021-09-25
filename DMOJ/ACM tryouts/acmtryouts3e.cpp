#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define pii pair<int, int>
#define ll long long

using namespace std;

struct qType
{
    pii coords;
    int dist;

    qType(pii COORDS, int DIST) { coords = COORDS, dist = DIST; }
};

int n, m;
bool isValid(pii x)
{
    if (x.first < 0 || x.second < 0 || x.first >= n || x.second >= m)
        return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        vector<string> grid(n);
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        for (int i =0; i < n; i++)
            cin >> grid[i];

        pii car;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 'C')
                    car.first = i, car.second = j;
            }
        }
        

        // BFS
        vector<int> howFar;
        queue<qType> que;
        que.push(qType(car, 0));
        while (!que.empty())
        {
            int dist = que.front().dist;
            pii curr = que.front().coords;
            que.pop();
            if (!isValid(curr))
                continue;
            if (visited[curr.first][curr.second])
                continue;
            if (grid[curr.first][curr.second] == '#')
                continue;
            visited[curr.first][curr.second] = true;

            if (grid[curr.first][curr.second] == 'S')
                howFar.push_back(dist);
            que.push(qType(pii(curr.first + 1, curr.second), dist + 1));
            que.push(qType(pii(curr.first - 1, curr.second), dist + 1));
            que.push(qType(pii(curr.first, curr.second + 1), dist + 1));
            que.push(qType(pii(curr.first, curr.second - 1), dist + 1));
        }
        sort(howFar.begin(), howFar.end());
        int out = 0;
        for (int i = 0; i < (int)howFar.size() - 1; i++)
        {
            out += howFar[i] * 2;
            out += 60;
        }
        out += howFar[howFar.size() - 1] + 60;

        cout << out << endl;
    }
}