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


q = int(input())
for i in range(q):
    k, f1, f2 = map(int, input().split())
    l, r = 0, k
    res = 0
    while l <= r:
        d = (l + r) // 2
        if iseq(f1 + 1, f2 + 1, d):
            res = d
            l = d + 1
        else:
            r = d - 1
    if res == k:
        print(0)
    elif s[f1 + res + 1] > s[f2 + res + 1]:
        print(1)
    elif s[f1 + res + 1] < s[f2 + res + 1]:
        print(-1)
