T = int(input())

for _ in range(T):
    s = input().split()
    for i in range(len(s)):
        s[i] = s[i][0].upper() + s[i][1:].lower()
    for i in range(len(s) - 1):
        s[i] = s[i][0] + '.'
    print(' '.join(s))
