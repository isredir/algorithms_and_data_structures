s = input()
n = len(s)
srev = s[::-1]
s = ' ' + s
srev = ' ' + srev
h, hrev, x = [0] * (n + 1), [0] * (n + 1), [0] * (n + 1)
x0 = 1007
p = 1000000009
h[0] = 0
hrev[0] = 0
x[0] = 1
for i in range(1, n + 1):
    x[i] = (x[i - 1] * x0) % p
    h[i] = (h[i - 1] * x0 + ord(s[i])) % p
    hrev[i] = (hrev[i - 1] * x0 + ord(srev[i])) % p


def iseq(f1, f2, k):
    return (h[f1 + k - 1] + hrev[f2 - 1] * x[k]) % p == \
           (hrev[f2 + k - 1] + h[f1 - 1] * x[k]) % p


def ispal(l, r):
    return iseq(l, n - r + 1, r - l + 1)


ans_odd = [0] * (n + 1)
for i in range(1, n + 1):
    l, r = 1, min(i, n - i + 1)
    while l <= r:
        d = (l + r) // 2
        if ispal(i - d + 1, i + d - 1):
            ans_odd[i] = d
            l = d + 1
        else:
            r = d - 1
ans_even = [0] * (n + 1)
for i in range(1, n + 1):
    l, r = 1, min(i, n - i)
    while l <= r:
        d = (l + r) // 2
        if ispal(i - d + 1, i + d):
            ans_even[i] = d
            l = d + 1
        else:
            r = d - 1
print(sum(ans_odd) + sum(ans_even))
