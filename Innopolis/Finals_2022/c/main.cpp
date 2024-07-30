#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

bool sito[(int)2e6];
vector<int> primes;
void sieve() {
    for (int i = 4; i <= 1e6; i += 2)
        sito[i] = true;
    for (int i = 3; i * i <= 1e6; i += 2) {
        if (sito[i])    
            continue;
        for (int j = i * i; j < 1e6; j += 2 * i)
            sito[j] = true;
    }

    for (int i = 1e4; i < 1e5; i++)
        if (!sito[i])
            primes.push_back(i);
}

string query(string num) {
    cout << num << endl;
    string out;
    cin >> out;
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sieve();
    
    string type;
    cin >> type;
    int t, l;
    cin >> l >> t;
    while (t--) {
        vector<set<int> > digs(5);
        set<int> oneToTen;
        for (int i = 0; i < 10; i++)
            oneToTen.insert(i);
        set<int> first = oneToTen;
        first.erase(0);
        set<int> last;
        last.insert(1);
        last.insert(3);
        last.insert(7);
        last.insert(9);

        digs[0] = first;
        digs[4] = last;
        digs[1] = oneToTen;
        digs[2] = oneToTen;
        digs[3] = oneToTen;

        bool done = false;
        for (int dig = 0; dig < 5;) {
            while (digs[dig].size() == 1 && dig < 5)
                dig++;
            if (dig == 5)
                break;
            // FINDING SUITABLE NUMBER
            string output = ""; int mxinfo = 0;
            for (int prime : primes) {
                int info = 0;
                string s = to_string(prime);
                for (int i = 0; i < 5; i++)
                    if (digs[i].find(s[i] - '0') != digs[i].end() && digs[i].size() != 1)
                        info++;
                if (digs[dig].find(s[dig] - '0') != digs[dig].end() && info > mxinfo)
                {
                    mxinfo = info;
                    output = s;
                }
            }

            // processing query
            string inp = query(output);
            if (inp == "+++++")
            {
                done = true;
                break;
            }

            for (int i = dig; i < 5; i++) {
                if (inp[i] == '+')
                {
                    digs[i] = set<int>();
                    digs[i].insert(output[i] - '0');
                }
                else 
                    digs[i].erase(output[i] - '0');
                
            }
        }

        if (!done) {
            string answer = "";
            for (int i = 0; i < 5; i++)
                for (int s : digs[i])
                    answer += '0' + s;

            query(answer);
        }
    }
}
