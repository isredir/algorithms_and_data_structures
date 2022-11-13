s = input()
s = ' ' + s
n = len(s) - 1
h, x = [0] * (n + 1), [0] * (n + 1)
x0 = 1007
p = 1000000009
h[0] = 0
x[0] = 1
for i in range(1, n + 1):
    x[i] = (x[i - 1] * x0) % p
    h[i] = (h[i - 1] * x0 + ord(s[i])) % p


def iseq(f1, f2, k):
    return (h[f1 + k - 1] + h[f2 - 1] * x[k]) % p == \
           (h[f2 + k - 1] + h[f1 - 1] * x[k]) % p


z = [0] * n
for i in range(1, n):
    l, r = 1, n - i
    while l <= r:
        d = (l + r) // 2
        if iseq(1, i + 1, d):
            z[i] = d
            l = d + 1
        else:
            r = d - 1
print(*z)
