n = int(input())
a = [int(i) for i in input().split()]
k = int(input())
b = [int(i) for i in input().split()]
for x in b:
    res1, res2 = 0, 0
    l = 0
    r = len(a) - 1
    while l < r:
        if x > a[(r + l) // 2]:
            l = (r + l) // 2 + 1
        else:
            r = (r + l) // 2
    if a[l] == x:
        res1 = l + 1
    l = 0
    r = len(a) - 1
    while l < r:
        if x < a[(r + l + 1) // 2]:
            r = (r + l + 1) // 2 - 1
        else:
            l = (r + l + 1) // 2
    if a[r] == x:
        res2 = r + 1
    print(res1, res2)
