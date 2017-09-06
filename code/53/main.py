def cut(k, i, j):
    # Chiều dọc, ngang và cao của khối bánh
    m = 2**k
    n = 2**k
    h = 1
    # Độ cao của ô chứa thưởng
    r = 1

    for _ in range(k):
        # Cắt ngang
        if i >= m/2:
            i = m-1 - i
            r = 2*h - r + 1
        m = m/2
        h = h * 2

        # Cắt dọc
        if j < n/2:
            j = n/2-1 - j
            r = 2*h - r + 1
        else:
            j = j - n/2
        n = n/2
        h = h * 2

    return 2**(2*k) - r + 1

k,p,q,u,v = list(map(int, input().split()))

print(cut(k,p,q), cut(k,u,v))
