from glolib import daj_n, daj_przelozonego, ruch

n = daj_n()

przelozeni = [0] * (n + 1)
for i in range(2, n + 1):
    przelozeni[i] = daj_przelozonego(i)

ruch(4)
ruch(7)
ruch(6)    
