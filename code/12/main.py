for _ in range(int(input())):
    n, b = [int(x) for x in input().split()]
    y = round(n / (2*b))
    print(-b * y * y + n * y)
