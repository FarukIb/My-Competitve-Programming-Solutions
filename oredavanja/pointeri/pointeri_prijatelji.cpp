#include <bits/stdc++.h>
#include <ctime>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct osoba {
    string ime;

    vector<osoba*> prijatelji;

    osoba(string Ime) {
        ime = Ime;
    }
};

map<string, osoba*> osobe;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    int broj_ljudi;
    cin >> broj_ljudi;
    for (int i = 0; i < broj_ljudi; i++) {
        string ime;
        cin >>ime;

        osobe[ime] = new osoba(ime);
    }

    for (int i = 0; i < broj_ljudi; i++) {
        string kome_unosimo;
        cin >> kome_unosimo;
        int broj_prijatelja;
        cin >> broj_prijatelja;
        for (int j = 0; j < broj_prijatelja; j++) {
            string ime_prijatelja;
            cin >> ime_prijatelja;
            osobe[kome_unosimo]->prijatelji.push_back(osobe[ime_prijatelja]);
        }
    }

    int pitanja;
    cin >> pitanja;
    while (pitanja--) {
        string ime1;
        string ime2;
        cin >> ime1 >> ime2;

        osoba *prva = osobe[ime1];
        bool je_li_tu = false;
        for (int i = 0; i < prva->prijatelji.size(); i++)
            if (prva->prijatelji[i]->ime == ime2)
                je_li_tu = true;

        cout << (int)je_li_tu << endl; 
    }
}