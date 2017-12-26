import itertools as it
import os

n = 50

clauses = []

def varnum(i, j):
    assert(i in range(n) and j in range(n))
    return i * n + j + 1

# each row contains at least one queen
for i in range(n):
    clauses.append([varnum(i, j) for j in range(n)])

# each row contains at most one queen
for i in range(n):
    for (j1, j2) in it.combinations(range(n), 2):
        clauses.append([-varnum(i, j1), -varnum(i, j2)])

# each column contains at most one queen
for j in range(n):
    for (i1, i2) in it.combinations(range(n), 2):
        clauses.append([-varnum(i1, j), -varnum(i2, j)])

# no two queens stay on the same diagonal
for (i1, i2) in it.combinations(range(n), 2):
    assert(i1 < i2)
    for (j1, j2) in it.product(range(n), repeat = 2):
        if i2 - i1 == abs(j2 - j1):
            clauses.append([-varnum(i1, j1), -varnum(i2, j2)])


with open('tmp.cnf', 'w') as f:
    f.write("p cnf {} {}\n".format(n * n, len(clauses)))
    for c in clauses:
        c.append(0);
        f.write(" ".join(map(str, c)) + "\n")

os.system("minisat tmp.cnf tmp.sat")

with open("tmp.sat", "r") as satfile:
    for line in satfile:
        if line.split()[0] == "UNSAT":
            print("There is no solution")
        elif line.split()[0] == "SAT":
            pass
        else:
            assignment = [int(x) for x in line.split()]

            #print("-" * (2 * n + 1))
            for i in range(n):
                print("|", end="")
                for j in range(n):
                    if varnum(i, j) in assignment:
                        print("x|", end="")
                    else:
                        print(" |", end="")

                print("")
                #print("-" * (2 * n + 1))
