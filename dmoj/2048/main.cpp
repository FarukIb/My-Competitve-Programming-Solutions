#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

typedef long long ll;

vector<ll> trans(2100);

class grid {
private:
public:
	vector<vector<int> > tiles;

	grid()
	{
		tiles.resize(4);
		for (int i = 0; i < 4; i++)
			tiles[i].resize(4);
	}

	inline bool operator==(const grid& b)
	{
        ll pow_12 = 1;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (tiles[i][j] != b.tiles[i][j])
					return false;
		return true;
	}

	bool operator < (const grid& o) const
	{ 
		ll pow_12 = 1, sum = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++, pow_12 = pow_12 * 12)
				sum += trans[o.tiles[i][j]] * pow_12;
		ll sum2 = 0; pow_12 = 1;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++, pow_12 = pow_12 * 12)
				sum2 += trans[tiles[i][j]] * pow_12;
		return sum2 < sum;
	}

	void shiftUp()
	{
		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 3; j++)
					if (tiles[j][i] == 0)
						swap(tiles[j][i], tiles[j + 1][i]);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (tiles[j][i] == tiles[j + 1][i])
				{
					tiles[j][i] *= 2, tiles[j + 1][i] = 0;
					break;
				}
			}
		}

		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 3; j++)
					if (tiles[j][i] == 0)
						swap(tiles[j][i], tiles[j + 1][i]);
	}
	
	void shiftDown()
	{
		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 3; j > 0; j--)
					if (tiles[j][i] == 0)
						swap(tiles[j][i], tiles[j - 1][i]);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j > 0; j--)
			{
				if (tiles[j][i] == tiles[j - 1][i])
				{
					tiles[j][i] *= 2, tiles[j - 1][i] = 0;
					break;
				}
			}
		}

		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 3; j > 0; j--)
					if (tiles[i][j] == 0)
						swap(tiles[i][j], tiles[i][j]);
	}

	void shiftRight()
	{
		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 1; j < 4; j++)
					if (tiles[i][j] == 0)
						swap(tiles[i][j], tiles[i][j - 1]);

		for (int i = 0; i < 4; i++)
		{
			bool broke = false;
			for (int j = 2; j >= 0; j--)
			{
				if (tiles[i][j] == tiles[i][j + 1])
				{
					tiles[i][j + 1] *= 2, tiles[i][j] = 0;
					broke = true;
					break;
				}
			}
		}

		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 1; j < 4; j++)
					if (tiles[i][j] == 0)
						swap(tiles[i][j], tiles[i][j - 1]);
	}

	void shiftLeft()
	{
		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 2; j >= 0; j--)
					if (tiles[i][j] == 0)
						swap(tiles[i][j], tiles[i][j + 1]);

		for (int i = 0; i < 4; i++)
		{
			bool broke = false;
			for (int j = 1; j < 4; j++)
			{
				if (tiles[i][j] == tiles[i][j - 1])
				{
					tiles[i][j - 1] *= 2, tiles[i][j] = 0;
					broke = true;
					break;
				}
			}
		}

		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 2; j >= 0; j--)
					if (tiles[i][j] == 0)
						swap(tiles[i][j], tiles[i][j + 1]);
	}
};

map<grid, bool> used;

bool exists(grid x)
{
	return used[x];
}

int maxi = 0;
void recur(grid curr)
{
	if (used[curr])
		return;
	used[curr] = true;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			maxi = max(maxi, curr.tiles[i][j]);

	grid a = curr;
	a.shiftUp();
	recur(a);

	grid b = curr;
	b.shiftDown();
	recur(b);

	grid c = curr;
	c.shiftRight();
	recur(c);

	grid d = curr;
	d.shiftLeft();
	recur(d);
}

int main()
{
    for (int i = 1, j = 1; i <= 2048; i *= 2, j++)
        trans[i] = j;

	for (int i = 0; i < 5; i++)
	{
		used.clear();
		maxi = 0;

		grid x;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cin >> x.tiles[i][j];

		recur(x);
		
		cout << maxi << endl;
	}
	
}