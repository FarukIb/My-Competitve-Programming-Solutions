from sys import exit
initialized = False;
active = False;
testcases = 0;
current_testcase = 0;
queries = 0;
weights = [0] * 7;
where = [0] * 7;
def read_testcase():
	global initialized, active, testcases, current_testcase, queries, where, weights
	if not initialized:
		init();
	if not active:
		queries = 0;
		current_testcase += 1;
		active = True
		weights = list(map(int, input().split(' ')))
		assert len(weights) == 7
		where = [0] * 7;

def init():
	global initialized, active, testcases, current_testcase, queries, where, weights
	if not initialized:
		initialized = True
		testcases = int(input());
		if testcases > 0:
			read_testcase();
		else:
			finalise();

def poloz_lewo(x):
	global initialized, active, testcases, current_testcase, queries, where, weights
	read_testcase();
	where[x - 1] = -1;

def poloz_prawo(x):
	global initialized, active, testcases, current_testcase, queries, where, weights
	read_testcase();
	where[x - 1] = 1;

def odloz(x):
	global initialized, active, testcases, current_testcase, queries, where, weights
	read_testcase();
	where[x - 1] = 0;

def wazenie():
	global initialized, active, testcases, current_testcase, queries, where, weights
	read_testcase();
	queries += 1;
	v = 0;
	for i in range(7):
		v += where[i] * weights[i];
	if v > 0:
		return 1;
	if v == 0:
		return 0;
	return -1;

def odpowiedz(a):
	global initialized, active, testcases, current_testcase, queries, where, weights
	read_testcase();
	if type(a) != list:
		print('Wywołanie funkcji odpowiedź z parametrem typu innego niż lista');
		exit(-1);
	for ai in a:
		print(ai, end=' ')
	print()
	print(f'Liczba wazen: {queries}')
	active = False;
	if testcases == current_testcase:
		exit(0)

def liczba_testow():
	init();
	return testcases;
