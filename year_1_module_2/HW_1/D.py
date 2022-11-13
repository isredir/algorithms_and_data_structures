n, k, m = [int(i) for i in input().split()]
parts = m * (k // m)
if parts != 0:
    count1 = (n - k + 1) // parts
    count2 = 1 if (n - k + 1) % parts != 0 else 0
    print((count1 + count2) * (k // m))
else:
    print(0)
