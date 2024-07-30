#include "combo.h"
#include <bits/stdc++.h>

using namespace std;

vector<string> T = {"A", "B", "X", "Y"};
map<string, int> t;

string get_first() {
	if (press("XY") != 0) {
		if (press("X") == 1)
			return "X";
		else
			return "Y";
	} else {
		if (press("A") == 1)
			return "A";
		else
			return "B";
	}
}

string make_string(string &pref, vector<string> &possible) {
	string one = pref + possible[0];
	string out = "";
	for (string a : possible)
		out += one + a;
	out += pref + possible[1];
	return out;
}

string get_next(string &pref, vector<string> &possible) {
	int val = press(make_string(pref, possible));
	if (val == pref.size() + 2) 
		return possible[0];
	else if (val == pref.size() + 1)
		return possible[1];
	return possible[2];
}

string get_last(string &pref, int N, vector<string> &possible) {
	for (int i = 0; i < 2; i++)
		if (press(pref + possible[i]) == N)
			return possible[i];
	return possible[2];
}

string guess_sequence(int N) {
	for (int i = 0; i <4; i++)
		t[T[i]] = i;

	string fc = get_first();
	if (N == 1)
		return fc;
	vector<string> possible;
	for (int i = 0; i < 4; i++)
		if (fc != T[i])
			possible.push_back(T[i]);

	string out = fc;
	for (int i = 0; i < N - 2; i++)
		out += get_next(out, possible);
	
	// getting last
	out += get_last(out, N, possible);

	return out;
}

// n - 2 + 2 + 2