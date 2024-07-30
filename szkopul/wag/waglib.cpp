#include <bits/stdc++.h>
#include <iostream>
using namespace std;

bool _initialized = false, _active = false;
int _current_testcase, _testcases, _queries;
int _weights[7], _where[7];

void _init();

void _read_testcase() {
	if (!_initialized)
		_init();
	if (!_active) {
		_queries = 0;
		_current_testcase++;
		_active = true;
		for (int i = 0; i < 7; ++i)
			std::cin >> _weights[i];
		for (int i = 0; i < 7; ++i)
			_where[i] = 0;
	}
}

void _init() {
	if (!_initialized) {
		_initialized = true;
		_current_testcase = 0;
		std::cin >> _testcases;
		_read_testcase();
	}
}

void poloz_lewo(int x) {
	_read_testcase();
	_where[x - 1] = -1;
}

void poloz_prawo(int x) {
	_read_testcase();
	_where[x - 1] = 1;
}

void odloz(int x) {
	_read_testcase();
	_where[x - 1] = 0;
}

int wazenie() {
	_read_testcase();
	_queries++;
	int v = 0;
	for (int i = 0; i < 7; ++i)
		v += _where[i] * _weights[i];
	if (v > 0) return 1;
	if (v == 0) return 0;
	return -1;
}

void odpowiedz(vector<int> a) {
	_read_testcase();
	for (int i = 0; i < 7; ++i)
		std::cout << a[i] << " ";
	std::cout << "\n";
	std::cerr << "Liczba wazen: " << _queries << "\n";
	_active = false;
	if (_testcases == _current_testcase)
		exit(0);
}

int liczba_testow() {
	_init();
	return _testcases;
}
