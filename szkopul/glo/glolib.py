import sys

_inited = False

def _initialize():
    global _inited, _n, _manager, _taken, _is_manager
    if _inited:
        return
    _inited = True
    _n = int(input())
    _manager = [0, 0] + [int(x) for x in input().split()]
    _taken = [0] * (_n + 1)
    _is_manager = [False] * (_n + 1)
    for i in range(2, _n + 1):
        _is_manager[_manager[i]] = True

def daj_n():
    global _n
    _initialize()
    return _n

def daj_przelozonego(v):
    global _manager
    _initialize()
    return _manager[v]

def ruch(x):
    global _n, _manager, _taken, _is_manager
    _initialize()
    _taken[x] = 1
    print('Zawodnik wybiera pracownika nr', x, file=sys.stderr)
    for i in range(2, _n + 1):
        if _taken[i] == 0 and not _is_manager[i]:
            _taken[i] = -1
            print('Jury wybiera pracownika nr', i, file=sys.stderr)
            return i
    for i in range(_n, 1, -1):
        if _taken[i] > 0:
            _taken[_manager[i]] += 1
        else:
            _taken[_manager[i]] -= 1
    if _taken[1] > 0:
        print('Zawodnik wygral')
    else:
        print('Jury wygralo')
    sys.exit(0)
