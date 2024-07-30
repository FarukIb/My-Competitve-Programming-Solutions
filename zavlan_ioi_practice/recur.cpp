#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct folder {
    string name;
    vector<folder*> children;
    folder() {}
};

folder* root;

void inp(folder* curr) {
    cin >>curr->name;
    int siz;
    cin >> siz;
    for (int i = 0; i < siz; i++) {
        folder* to_add = new folder();
        inp(to_add);
        curr->children.push_back(to_add);
    }
}

void out(folder*curr, int dep) {
    if (dep != -1) {
        for (int i = 0;i <dep; i++)
            cout << ".";
        cout <<curr->name <<"\n";
    }
    for (auto fol : curr->children) {
        if (fol->name[0] == 'a')
            continue;
        out(fol, dep + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    root = new folder();
    inp(root);
    out(root, -1);
}