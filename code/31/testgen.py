# Sinh test
import random
k = random.randrange(60) + 1;
l = random.sample(range(64), k)
print(k)
for u in l:
    print(int(u/8) + 1, u%8 + 1, random.randrange(1000000000))
