import random
n = 10000
m = 50000
print(n, m)
edges = random.sample(range(n*n), m)
for x in e:
    u = x % n + 1
    v = x // n + 1
    print(u, v)
