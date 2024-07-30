#include <iostream>
#include <vector>
#include "glolib.h"

int _n;
std::vector<int> _manager;

bool _inited = false;
std::vector<int> _taken;
std::vector<bool> _is_manager;

void _initialize() {
    if (_inited) {
        return;
    }
    _inited = true;
    std::cin >> _n;
    _manager.resize(_n + 1);
    _taken.resize(_n + 1);
    _is_manager.resize(_n + 1);
    for (int i = 2; i <= _n; i++) {
        std::cin >> _manager[i];
        _is_manager[_manager[i]] = true;
    }
}

int daj_n() {
    _initialize();
    return _n;
}

int daj_przelozonego(int v) {
    _initialize();
    return _manager[v];
}

int ruch(int x) {
    _initialize();
    _taken[x] = 1;
    std::cerr << "Zawodnik wybiera pracownika nr " << x << std::endl;
    for (int i = 2; i <= _n; i++) {
        if (_taken[i] == 0 && !_is_manager[i]) {
            _taken[i] = -1;
            std::cerr << "Jury wybiera pracownika nr " << i << std::endl;
            return i;
        }
    }
    for (int i = _n; i > 1; i--) {
        if (_taken[i] > 0) {
            _taken[_manager[i]]++;
        } else {
            _taken[_manager[i]]--;
        }
    }
    if (_taken[1] > 0) {
        std::cout << "Zawodnik wygral" << std::endl;
    } else {
        std::cout << "Jury wygralo" << std::endl;
    }
    exit(0);
}
