#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct fold {
    map<string, fold*> children;
    int id = 0;
    string path;
    fold* par;

    fold() {}
    fold(string pth, int ID, fold* parr) {
        path = pth, id = ID, par = parr;
    }
};

fold* root = new fold("/", 0, nullptr);
int ccc = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int Q;
    cin >> Q;
    fold* curr = root;
    while (Q--) {
        string op;
        cin >> op;
        if (op == "mkdir") {
            string name;
            cin >> name;
            if (curr->children.find(name) != curr->children.end())
                cout << "greska\n";
            else    
            {
                string newpath;
                if (curr->par == nullptr)
                    newpath = "/" + name;
                else
                    newpath = curr->path + "/" + name;
                fold* neww = new fold(newpath, ++ccc, curr);
                
                curr->children[name] = neww;
                cout << neww->path << "\n";
            }
        }
        else if (op == "rmdir") {
            string name; cin >> name;
            if (curr->children.find(name) == curr->children.end())
                cout << "greska\n";
            else {
                fold* thatone = curr->children[name];
                if (!thatone->children.empty())
                    cout << "greska\n";
                else
                {
                    cout << thatone->path << "\n";
                    delete thatone;
                    curr->children.erase(name);
                }
            }
        }
        else if (op == "cd") {
            string name; cin >> name;
            if (name != "..") {
                if (curr->children.find(name) == curr->children.end())
                    cout << "greska\n";
                else
                {
                    curr = curr->children[name];
                    cout << curr->path << "\n";
                }
            }
            else {
                if (curr->par == nullptr)
                    cout << "greska\n";
                else
                {
                    curr = curr->par;
                    cout << curr->path << "\n";
                }
            }
        }
    }
}
