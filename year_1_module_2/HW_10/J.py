n, m = map(int, input().split())
a = [[0] * (m + 1)]
h = [[0] * (m + 1)]
for i in range(n):
    a.append([0] + [ord(i) for i in input()])
    h.append([0] * (m + 1))
mod = 10**18
p = 301703
q = 239017
pp, qq = [0] * 2001, [0] * 2001
pp[0], qq[0] = 1, 1
for i in range(1, 2001):
    pp[i] = (pp[i - 1] * p) % mod
    qq[i] = (qq[i - 1] * q) % mod
for i in range(1, n + 1):
    for j in range(1, m + 1):
        h[i][j] = (h[i - 1][j] * q +
                   h[i][j - 1] * p -
                   h[i - 1][j - 1] * p * q + a[i][j]) % mod


def gethash(u, l, d, r):
    return h[d][r] - h[d][l - 1] * pp[r - l + 1] - \
           h[u - 1][r] * qq[d - u + 1] + \
           h[u - 1][l - 1] * pp[r - l + 1] * qq[d - u + 1]


def iseq(u1, l1, d1, r1, u2, l2, d2, r2):
    return (h[d1][r1] + h[d2][l2 - 1] * pp[r2 - l2 + 1] +
            h[u2 - 1][r2] * qq[d2 - u2 + 1] +
            h[u1 - 1][l1 - 1] * pp[r1 - l1 + 1] * qq[d1 - u1 + 1]) % mod == \
           (h[d2][r2] + h[d1][l1 - 1] * pp[r1 - l1 + 1] +
            h[u1 - 1][r1] * qq[d1 - u1 + 1] +
            h[u2 - 1][l2 - 1] * pp[r2 - l2 + 1] * qq[d2 - u2 + 1]) % mod


mins = 10**9
mini, minj = 0, 0
flag = False
for i in range(1, n):
    for j in range(1, m // 2 + 1):
        if iseq(1, 1, n - i, m - j, i + 1, j + 1, n, m):
            if i + j < mins:
                mins = i + j
                mini = i
                minj = j
                flag = True
                break
    if flag:
        break
shift = 0
for j in range(1, m + 1):
    if iseq(1, 1, mini, m - j + 1, mini + 1, j, mini + mini, m):
        shift = j - 1
        break
k = 1
while k < m:
    if iseq(1, 1, mini, m - k, 1, k + 1, mini, m):
        break
    k += 1
print(mini, k, shift)
