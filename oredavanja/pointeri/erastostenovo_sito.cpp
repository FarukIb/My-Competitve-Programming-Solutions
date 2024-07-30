#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

vector<bool> je_li_prost;

void napravi(int granica) {
    je_li_prost.resize(granica, false);

    for (int i = 2; i < granica; i++) {
        if (je_li_prost[i])
            continue;
        for (int j = 2 * i; j < granica; j += i)
            je_li_prost[j] = true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    
}