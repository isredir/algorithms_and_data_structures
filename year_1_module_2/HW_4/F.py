n, k = [int(i) for i in input().split()]
a = [int(i) for i in input().split()]
b = [int(i) for i in input().split()]
for x in b:
    l = 0
    r = len(a) - 1
    while l < r:
        if x > a[(r + l) // 2]:
            l = (r + l) // 2 + 1
        else:
            r = (r + l) // 2
    if a[l] == x:
        print('YES')
    else:
        print('NO')
