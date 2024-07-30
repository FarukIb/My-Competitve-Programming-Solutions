
from sage.all import *
inpu = open('output.txt', 'r')
Lines = inpu.readlines()
res = open('rex.txt', 'w')

def is_integer_solution(solution):
    try:
        if (type(solution) != list):
            return solution.rhs() in ZZ
        return all(eq.rhs() in ZZ for eq in solution)
    except:
        return False

res.writelines('100\n')
idx = 0
left = 0
n = 0
k = 0
a = var('a')
b = var('b')
c = var('c')
variables = []
equations = []
for line in Lines:
    if (left == 0):
        if (idx != 0):
            sols = []
            if (k == 1):
                sols = solve(equations, a)
            elif (k == 2):
                sols = solve(equations, a, b)
            else:
                sols = solve(equations, a, b, c)
            integer_solutions = [s for s in sols if is_integer_solution(s)]
            if len(integer_solutions) != 0:
                out = str(idx)
                for guy in integer_solutions:
                    if (type(guy) != list):
                        out += ' ' + str(guy.rhs())
                    else:
                        for guy2 in guy:
                            out += ' ' + str(guy2.rhs())
                res.writelines(out)
                print(out)
        currarr = line.split()
        n = currarr[0]
        k = int(currarr[1])
        left = int(k)
        equations = []
        variables = []
        if (k >= 1):
            variables.append(a)
        if (k >= 2):
            variables.append(b)
        if (k >= 3):
            variables.append(c)
        idx = idx + 1
    else:
        neww = line[0:(len(line) - 1)]
        expression = SR(neww)
        equations.append(expression)
        left -= 1