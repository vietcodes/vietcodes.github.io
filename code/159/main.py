n, k = (int(x) for x in input().split())

f0 = [0 for i in range(n+1)]
f1 = [0 for i in range(n+1)]

f0[0] = 1
f1[0] = 1

sum_f0 = f0[0]
sum_f1 = f1[0]

for i in range(1, n+1):
    if i-k-1 >= 0:
        sum_f1 -= f1[i-k-1]
        sum_f0 -= f0[i-k-1]
    f0[i] = sum_f1
    f1[i] = sum_f0

    sum_f0 += f1[i]
    sum_f1 += f0[i]

print(f0[n] + f1[n])
