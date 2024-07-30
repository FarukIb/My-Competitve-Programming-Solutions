#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    int l = 0;
    while (cin >> s) {
        vector<int> guys;
        char sign;
        string temp = "";
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '?')
            {
                sign = s[i];
                break;
            }
            else if (s[i] == '-' or s[i] == '+')
            {
                sign = s[i];
                guys.push_back(stoi(temp));
                temp = "";
            }
            else if (s[i] == '=') {
                guys.push_back(stoi(temp));
                temp = "";
            }
            else {
                temp += s[i];
            }
        }

        if (sign == '?')
            continue;
        guys.push_back(stoi(temp));
        if (sign == '+')
        {
            if (guys[0] + guys[1] == guys[2])
                l++;
        }
        else {
            if (guys[0] - guys[1] == guys[2])
                l++;
        }
    }

    cout << l << "\n";
}