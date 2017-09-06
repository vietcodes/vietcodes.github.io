from itertools import permutations
import random

T = 1
print(T)
for _ in range(T):
    n = 1000
    m = 100000
    k = 1000000
    edges = [(u, v) for u, v in permutations(range(n), 2)]
    l = random.sample(edges, m)
    print(n, m)
    for u, v in l:
        print(u + 1, v + 1, random.randrange(k) + 1)
