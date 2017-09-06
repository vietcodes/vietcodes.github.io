# Code sinh test
import random
T = 1
print(T)
for i in range(T):
    n = 100000
    m = 1000000
    Q = 30
    print(n, m, Q)
    for j in range(m):
        x, y = random.sample(range(n), 2)
        w = random.randrange(1000000000) + 1
        print(x+1, y+1, w)
    for j in range(Q):
        k = 100
        print(random.randrange(m) + 1, k, end=' ')
        l = random.sample(range(m), k)
        for x in l:
            print(x+1, random.randrange(1000000000)+1, end=' ')
        print('')
