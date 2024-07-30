#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct node {
    string path;
    node* par;
    map<string, node*> children;

    node() {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    node* my = new node();
    my->path = "";

    while (n--) {
        string type;
        cin >> type;

        if (type == "cd") {
            string s;
            cin >>s;

            if (s == "..")
            {
                if (my->path == "")
                    cout <<"greska\n";
                else
                {
                    my = my->par;
                    if (my->path == "")
                        cout <<"/\n";
                    else
                        cout << my->path << "\n";
                }
            }
            else if (!my->children.count(s))
                cout << "greska\n";
            else
            {
                my = my->children[s];
                if (my->path == "")
                    cout <<"/\n";
                else
                    cout << my->path << "\n";
            }
        }
        else if (type == "mkdir") {
            string s;
            cin >>s;

            if (my->children.count(s)) {
                cout << "greska\n";
            } else {
                node* neww = new node();
                neww-> par = my;
                neww->path = my->path + "/" + s;
                my->children[s] = neww;
                cout << neww->path <<"\n";
            }
        } else if (type == "rmdir") {
            string s;
            cin >>s;

            if (!my->children.count(s)) {
                cout << "greska\n";
            } else {
                node* torem = my->children[s];
                if (torem->children.size() != 0)
                    cout << "greska\n";
                else
                    my->children.erase(s);
            }
        }
    }
}