def equal(x1, y1, x2, y2, x3, y3, x4, y4):
    return (x1 - x2)**2 + (y1 - y2)**2 == (x3 - x4)**2 + (y3 - y4)**2


def parallel(x1, y1, x2, y2, x3, y3, x4, y4):
    if x1 - x2 == 0 or x3 - x4 == 0:
        return x1 - x2 == x3 - x4
    else:
        return (y1 - y2) / (x1 - x2) == (y3 - y4) / (x3 - x4)


n = int(input())
for _ in range(n):
    d = [int(i) for i in input().split()]
    x1, y1, x2, y2 = d[0], d[1], d[2], d[3]
    x3, y3, x4, y4 = d[4], d[5], d[6], d[7]
    if equal(x1, y1, x2, y2, x3, y3, x4, y4) and \
            parallel(x1, y1, x2, y2, x3, y3, x4, y4):
        print('YES')
    elif equal(x1, y1, x3, y3, x2, y2, x4, y4) and \
            parallel(x1, y1, x3, y3, x2, y2, x4, y4):
        print('YES')
    elif equal(x1, y1, x4, y4, x2, y2, x3, y3) and \
            parallel(x1, y1, x4, y4, x2, y2, x3, y3):
        print('YES')
    else:
        print('NO')
