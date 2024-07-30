#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool win_cmp(pii a, pii b) {
    return a.second < b.second;
}

bool loss_cmp(pii a, pii b) {
    return a.second > b.second;
}

const int n = 4;
const int m = 4;
const int k = 4;

vector<int> pow3(30, 1);

int get_col(int mask, int r, int c) {
    int id = r * m + c;
    mask /= pow3[id];
    return mask % 3;
}

pii num_placed(int mask) {
    pii num(0, 0);
    while (mask > 0) {
        if (mask % 3)
        {
            if (mask % 3 == 1)
                num.first++;
            else
                num.second++;
        }
        mask /= 3;
    }
    return num;
}

int get_winner(int mask) {
    int num[3] = {0, 0, 0};
    for (int i = 0; i + k <= n; i++) {
        for (int j = 0; j < m; j++) {
            // vert
            int num[3] = {0, 0, 0};
            for (int d = 0; d < k; d++)
                num[get_col(mask, i + d, j)]++;
            if (num[1] == k)
                return 1;
            if (num[2] == k)
                return 2;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + k <= m; j++) {
            // hori
            num[0] = num[1] = num[2] = 0;
            for (int d = 0; d < k; d++)
                num[get_col(mask, i, j + d)]++;
            if (num[1] == k)
                return 1;
            if (num[2] == k)
                return 2;
        }
    }
    for (int i = 0; i + k <= n; i++) {
        for (int j = 0; j + k <= m; j++) {
            num[0] = num[1] = num[2] = 0;
            for (int d = 0; d < k; d++)
                num[get_col(mask, i + d, j + d)]++;
            if (num[1] == k)
                return 1;
            if (num[2] == k)
                return 2;
        }
    }

    for (int i = 0; i + k <= n; i++) {
        for (int j = k - 1; j < m; j++) {
            num[0] = num[1] = num[2] = 0;
            for (int d = 0; d < k; d++)
                num[get_col(mask, i + d, j - d)]++;
            if (num[1] == k)
                return 1;
            if (num[2] == k)
                return 2;
        }
    }
    return 0;
}

int cmp(int a, int b) {
    return num_placed(a).first + num_placed(a).second > num_placed(b).first + num_placed(b).second;
}

vector<int> state; // 0 is draw, 1 is first player wins 2 is second player wins
vector<int> dist_to_end;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 1; i < 30; i++)
        pow3[i] = pow3[i - 1] * 3;
    
    state = dist_to_end = vector<int>(pow3[n * m]);

    vector<int> states;
    for (int i = 0; i < pow3[n * m]; i++)
    {
        pii num = num_placed(i);
        if (num.first >= num.second and num.first - num.second <= 1)
            states.push_back(i);
    }
    sort(all(states), cmp);
    fstream fout("rules" + to_string(n) + "x" + to_string(m) + "x" + to_string(k) + ".txt");
    //fout << n << " " << m << " " << k << endl;
    int num_so_far = 0;
    for (int mask : states) {
        num_so_far++;
        if (num_so_far % 100000 == 0)
            cout << (double)num_so_far / (double)states.size() * 100 << "%" << endl;
        int winner = get_winner(mask);
        if (winner == 1) {
            dist_to_end[mask] = 0;
            state[mask] = 1;
            fout << mask << " 1 0" << endl;
            continue;
        } else if (winner == 2) {
            dist_to_end[mask] = 0;
            state[mask] = 2;
            fout << mask << " 2 0" << endl;
            continue;
        }

        int num = num_placed(mask).first + num_placed(mask).second;
        int turn = num % 2 + 1, other = (num + 1) % 2 + 1;
        vector<pii> draws, wins, losses;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (get_col(mask, i, j) != 0)
                    continue;
                
                int child = mask + pow3[i * m + j] * turn;
                if (state[child] == 0)
                    draws.push_back(pii(child, dist_to_end[child]));
                else if (state[child] == turn)
                    wins.push_back(pii(child, dist_to_end[child]));
                else
                    losses.push_back(pii(child, dist_to_end[child]));
            }
        }

        if (wins.size() > 0) {
            sort(all(wins), win_cmp);
            dist_to_end[mask] = wins[0].second + 1;
            state[mask] = turn;
            while (wins.back().second != wins[0].second)
                wins.pop_back();
            fout << mask << " " << turn << " " << wins.size();
            for (auto &[msk, wn] : wins)
                fout << " " << msk;
            fout << endl;
        } else if (draws.size() > 0 || (wins.size() == 0 and losses.size() == 0)) {
            state[mask] = 0;
            fout << mask << " " << 0 << " " << draws.size();
            for (auto &[msk, wn] : draws)
                fout << " " << msk;
            fout << endl;
        } else {
            sort(all(losses), loss_cmp);
            dist_to_end[mask] = losses[0].second + 1;
            while (losses.back().second != losses[0].second)
                losses.pop_back();
            state[mask] = other;
            fout << mask << " " << other << " " << losses.size();
            for (auto &[msk, wn] : losses)
                fout << " " << msk;
            fout << endl;
        }
    }
}