w, h, n = [int(i) for i in input().split()]
l, r = 0, min(w, h) * n
while l < r:
    x = (l + r) // 2
    if (x // w) * (x // h) < n:
        l = x + 1
    else:
        r = x
print(r)
