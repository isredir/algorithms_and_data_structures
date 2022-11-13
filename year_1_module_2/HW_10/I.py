n, m = map(int, input().split())
s = []
for _ in range(n):
    s.append(input())
h1, h2, x = [], [], [0] * 101
for i in range(n + 1):
    h1.append([0] * (m + 1))
    h2.append(([0] * (m + 1)))
x0 = 239017
x[0] = 1
for i in range(100):
    x[i + 1] = x[i] * x0
for i in range(n):
    for j in range(m):
        h1[i][j + 1] = h1[i][j] * x0 + ord(s[i][j])
for i in range(n):
    for j in range(m - 1, -1, -1):
        h2[i][j] = h2[i][j + 1] * x0 + ord(s[i][j])


def geth1(i, l, r):
    return h1[i][r + 1] - h1[i][l] * x[r - l + 1]


def geth2(i, l, r):
    return h2[i][l] - h2[i][r + 1] * x[r - l + 1]


def iseq(i1, i2, l, r):
    return geth1(i1, l, r) == geth2(i2, l, r)


summ = 0
for i in range(n):
    for j in range(m):
        k = m
        while not(j - k >= 0 and j + k < m):
            k -= 1
        l = 0
        while i - l >= 0 and i + l < n:
            while k >= 0 and not iseq(i - l, i + l, j - k, j + k):
                k -= 1
            summ += k + 1
            l += 1
for i in range(n):
    for j in range(m):
        k = m
        while not(j - k >= 0 and j + k + 1 < m):
            k -= 1
        l = 0
        while i - l >= 0 and i + l < n:
            while k >= 0 and not iseq(i - l, i + l, j - k, j + k + 1):
                k -= 1
            summ += k + 1
            l += 1
for i in range(n):
    for j in range(m):
        k = m
        while not(j - k >= 0 and j + k < m):
            k -= 1
        l = 0
        while i - l >= 0 and i + l + 1 < n:
            while k >= 0 and not iseq(i - l, i + l + 1, j - k, j + k):
                k -= 1
            summ += k + 1
            l += 1
for i in range(n):
    for j in range(m):
        k = m
        while not(j - k >= 0 and j + k + 1 < m):
            k -= 1
        l = 0
        while i - l >= 0 and i + l + 1 < n:
            while k >= 0 and not iseq(i - l, i + l + 1, j - k, j + k + 1):
                k -= 1
            summ += k + 1
            l += 1
print(summ)
