s = input()
N = len(s)

f = [[0 for j in range(N)] for i in range(N)]

def calc(l, r):
    if f[l][r] != -1:
        return f[l][r]

    if l == r:
        f[l][r] = 1
        return f[l][r]
    elif l > r:
        f[l][r] = 0
        return f[l][r]

    f[l][r] = calc(l, r-1) + calc(l+1, r) - calc(l+1, r-1)
    if s[l] == s[r]:
        f[l][r] += 1 + calc(l+1, r-1)
    return f[l][r]

print(calc(0, N-1))
