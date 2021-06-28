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

#define pii pair<int, int>
#define ll long long

using namespace std;

int tree[(int)1e6];
class BIT
{
private:
int n;
public:
 
BIT(int sizeOfTree)
{
    n = sizeOfTree;
}
 
void update(int index, int value)
{
    index++;
    while (index < n)
        tree[index] += value, index += index & (-index);
}
 
int query(int index)
{
    index++;
    int out = 0;
    while (index > 0)
        out += tree[index], index -= index & (-index);
    return out;
}
 
};

void printVector(vector<int> toBePrinted)
{
	for (int i : toBePrinted)
		cout << i << " ";
	cout << endl;
}

map<int, vector<int> > located;
map<int, int> used;
map<int, bool> matched;

ll count_swaps(vector<int> S)
{
	int n = S.size();
	BIT passed(n);
	vector<int> dummy;
	for (int i : S)
		located[i] = dummy, used[i] = -1;
	
	for (int i = 0; i < n; i++)
		located[S[i]].push_back(i);
	
	ll out = 0;
	for (int i = 0; i < n; i++)
	{
		if (matched[i])
			continue;
		int index = upper_bound(located[-S[i]].begin(), located[-S[i]].end(), used[-S[i]]) - located[-S[i]].begin();
		int val = located[-S[i]][index];
		
		used[S[i]] = max(used[S[i]], i);
		used[-S[i]] = max(used[-S[i]], val);
		
		
		matched[val] = true;
		
		int howManyHavPassedVal = passed.query(n - val - 1), howManyHavPassedCurr = passed.query(n - i - 1);
		int swaps = (val + howManyHavPassedVal) - (i + howManyHavPassedCurr);
		
		passed.update(n - val - 1, 1);
		if (S[i] < 0)
			swaps--;
		out += swaps;
	}
	
	return out;
}

int main()
{
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << count_swaps(arr) << endl;
	return 0;
}
