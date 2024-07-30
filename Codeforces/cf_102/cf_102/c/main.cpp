#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<string> up = {
        "###",
        ".#.",
        ".#."
};
vector<string> rightt = {
        "..#",
        "###",
        "..#"
};
vector<string> down = {
        ".#.",
        ".#.",
        "###"
};
vector<string> leftt = {
        "#..",
        "###",
        "#.."
};

vector<vector<string> > plows = {up, rightt, down, leftt};

vector<string> convert(vector<string> &guy, char my) {
    vector<string> neww;
    for (int i = 0; i < guy.size(); i++){
        neww.push_back("");
        for (int j = 0; j < guy[i].size(); i++) {
            if (guy[i][j] == '.')
                neww[i] += '.';
            else
                neww[i] += my;
        }
    }
    return neww;
}

set<string> guys;

//vector<vector<int> > best_mat;

int best = -1;
vector<string> bestie;
bool exists(vector<string> &guy) {
    string decompressed;
    for (string k : guy)    
        decompressed += k;
    if (!guys.count(decompressed))
    {
        guys.insert(decompressed);
        return false;
    }
    return true;
}

int n, m;
void recur(int num, vector<string> general, vector<string> specific) {
    if (exists(general))
        return;
    if (num > best)
        best = num, bestie = specific;
    
    int possible = num + (n * m - num * 5) / 5;
    if (possible <= best)
        return;
    
    int mi = 0, mj = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (general[i][j] == '#')
                mi = max(mi, i), mj = max(mj, j);
    }

    for (vector<string> plow : plows) {
        for (int i = 0; i < n - 2; i++) {
            for (int j = 0; j < m - 2; j++) {
                bool broke = false;
                for (int i2 = 0; i2 < 3; i2++)
                    for (int j2 = 0; j2 < 3; j2++)
                        if (plow[i2][j2] == '#' && general[i + i2][j + j2] != '.')
                            broke = true;
                
                if (broke)
                    continue;
                vector<string> neww_gen = general;
                vector<string> neww_spec = specific;
                for (int i2 = 0; i2 < 3; i2++)
                    for (int j2 = 0; j2 < 3; j2++)
                        if (plow[i2][j2] == '#')
                            neww_gen[i + i2][j + j2] = '#', neww_spec[i + i2][j + j2] = (char)(num + 'A');

                recur(num + 1, neww_gen, neww_spec);
            }
        }
    }
}

vector<string> nine_nine = {"AAABBBCCC",
".AI.BJ.C.",
".AI.BJ.C.",
"MIIIJJJ.G",
"MMMDDDGGG",
"MEEEDFFFG",
".KE.DHFL.",
".KEHHHFL.",
"KKK..HLLL" };

vector<string> nine_seven = {"AAABBB.",
".A..BF.",
".AD.BF.",
"DDDIFFF",
"J.DIIIE",
"JJJIEEE",
"JGCCCHE",
".G.C.H.",
"GGGCHHH"
};

vector<string> nine_eight = {"AAABBB.E",
".AH.BEEE",
".AH.B.FE",
"KHHHFFF.",
"KKKCCCFG",
"KDDDCGGG",
".IDLC.JG",
".IDLLLJ.",
"IIIL.JJJ" };

vector<string> eight_eight = {"AAABBB..",
".A..BCCC",
"IA..B.C.",
"IIIDDDCF",
"IEEEDFFF",
".GEJD.HF",
".GEJJJH.",
"GGGJ.HHH"
};

vector<string> eight_seven = {
"AAA.BBB",
".ACCCB.",
"GA.CHB.",
"GGGCHHH",
"GDDDH.E",
".FDIEEE",
".FDIIIE",
"FFFI..."
};

vector<string> seven_seven = {
"AAA.BBB",
".ACCCB.",
"HA.C.BE",
"HHHCEEE",
"HFDDDGE",
".F.D.G.",
"FFFDGGG"
};

vector<string> nine_six = {
"AAABBB",
".A..B.",
".A.GB.",
"CCCGGG",
".CEG.D",
".CEDDD",
"HEEEFD",
"HHH.F.",
"H..FFF"
};

vector<string> six_eight {
"AAABBB..",
".A..BCCC",
".A.DB.C.",
"GDDDF.CE",
"GGGDFEEE",
"G..FFF.E"
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    //best_mat.resize(n + 1, vector<int>(m + 1, 0));

    if (n == 9 && m == 9) {
        cout << "13\n";
        for (int i = 0; i < 9; i++)
            cout << nine_nine[i] << "\n";
    }
    else if (n == 9 && m == 8) {
        cout << "12\n";
        for (int i = 0; i < 9; i++)
            cout << nine_eight[i] << "\n";
    }
    else if (n == 8 && m == 9) {
        cout << "12\n";
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 9; j++)
                cout << nine_eight[j][i];
            cout << "\n";
        }
    }
    else if (n == 9 && m == 7) {
        cout << "10\n";
        for (int i = 0; i < 9; i++)
            cout << nine_seven[i] <<"\n";
    }
    else if (n == 7 && m == 9) {
        cout << "10\n";
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 9; j++)
                cout << nine_seven[j][i];
            cout << "\n";
        }
        
    }
    else if (n == 8 && m == 8) {
        cout << "10\n";
        for (int i = 0; i < 8; i++)
            cout << eight_eight[i] << "\n";
    }
    else if (n == 8 && m == 7) {
        cout << "9\n";
        for (int i = 0; i < 8; i++)
            cout << eight_seven[i] << "\n";
    }
    else if (n == 7 && m == 8) {
        cout << "9\n";
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 8; j++)
                cout << eight_seven[j][i];
            cout << "\n";
        }
    }
    else if (n == 7 && m == 7) {
        cout << "8\n";
        for (int i = 0; i < 7; i++)
            cout << seven_seven[i] <<"\n";
    }
    else if (n == 9 && m == 6) {
        cout << "8\n";
        for (int i = 0; i < 9; i++)
            cout << nine_six[i] << "\n";
    }
    else if (n == 6 && m == 9) {
        cout << "8\n";
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 9; j++)
                cout << nine_six[j][i];
            cout << "\n";
        }
    }
    else if (n == 6 && m == 8) {
        cout << "7\n";
        for (int i = 0; i < 6; i++) 
            cout << six_eight[i] << "\n";
    }
    else if (n == 8 && m == 6) {
        cout << "7\n";
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 6; j++)
                cout << six_eight[j][i];
            cout << "\n";
        }
    }
    else {
        vector<string> empty(n, "");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                empty[i] += '.';
        recur(0, empty, empty);

        cout << best << "\n";
        for (string s : bestie)
            cout << s << "\n";
    }







}

/*
9 9
13
"AAABBBCCC"
".AI.BJ.C."
".AI.BJ.C."
"MIIIJJJ.G"
"MMMDDDGGG"
"MEEEDFFFG"
".KE.DHFL."
".KEHHHFL."
"KKK..HLLL"

9 8
12
"AAABBB.E"
".AH.BEEE"
".AH.B.FE"
"KHHHFFF."
"KKKCCCFG"
"KDDDCGGG"
".IDLC.JG"
".IDLLLJ."
"IIIL.JJJ"

9 7
10
"AAABBB."
".A..BF."
".AD.BF."
"DDDIFFF"
"J.DIIIE"
"JJJIEEE"
"JGCCCHE"
".G.C.H."
"GGGCHHH"

8 8
10
"AAABBB.."
".A..BCCC"
"IA..B.C."
"IIIDDDCF"
"IEEEDFFF"
".GEJD.HF"
".GEJJJH."
"GGGJ.HHH"

8 7
9
"AAA.BBB"
".ACCCB."
"GA.CHB."
"GGGCHHH"
"GDDDH.E"
".FDIEEE"
".FDIIIE"
"FFFI..."

7 7
8
AAA.BBB
.ACCCB.
HA.C.BE
HHHCEEE
HFDDDGE
.F.D.G.
FFFDGGGž

9 6
8
AAABBB
.A..B.
.A.GB.
CCCGGG
.CEG.D
.CEDDD
HEEEFD
HHH.F.
H..FFF
*/