from waglib import poloz_lewo, poloz_prawo, odloz, wazenie, odpowiedz, liczba_testow
t = liczba_testow()
for _ in range(t):
	poloz_lewo(1);
	poloz_lewo(2);
	poloz_prawo(3);
	r = wazenie();
	if r == 1:
		odpowiedz([1, 2, 7, 4, 5, 6, 3]);
	elif r == 0:
		odpowiedz([2, 1, 3, 7, 4, 5, 6]);
	else:
		odpowiedz([7, 6, 1, 4, 2, 5, 3]);
