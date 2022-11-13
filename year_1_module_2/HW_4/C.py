def check(points, a, b):
    d = 0
    for i in points:
        if a == i[0] and b == i[1]:
            return 10**9
        d += abs(a - i[0])
        d += abs(b - i[1])
    return d


n = int(input())
points = []
x, y = [], []
for _ in range(n):
    a, b = [int(i) for i in input().split()]
    points.append([a, b])
    x.append(a)
    y.append(b)
x, y = sorted(x), sorted(y)
left = x[(len(x) - 1)//2]
down = y[(len(y) - 1)//2]
dist = 10**9
res_x, res_y = 0, 0
d = check(points, left + 1, down + 1)
if d < dist:
    dist = d
    res_x, res_y = left + 1, down + 1
d1 = check(points, left + 2, down + 1)
d2 = check(points, left + 1, down + 2)
d3 = check(points, left, down + 1)
d4 = check(points, left + 1, down)
if d1 < dist:
    dist = d1
    res_x, res_y = left + 2, down + 1
if d2 < dist:
    dist = d2
    res_x, res_y = left + 1, down + 2
if d3 < dist:
    dist = d3
    res_x, res_y = left, down + 1
if d4 < dist:
    dist = d4
    res_x, res_y = left + 1, down
for i in points:
    d1 = check(points, i[0], i[1] + 1)
    d2 = check(points, i[0] + 1, i[1])
    d3 = check(points, i[0] - 1, i[1])
    d4 = check(points, i[0], i[1] - 1)
    if d1 < dist:
        dist = d1
        res_x, res_y = i[0], i[1] + 1
    if d2 < dist:
        dist = d2
        res_x, res_y = i[0] + 1, i[1]
    if d3 < dist:
        dist = d3
        res_x, res_y = i[0] - 1, i[1]
    if d4 < dist:
        dist = d4
        res_x, res_y = i[0], i[1] - 1
print(res_x, res_y)
