n, m = map(int, input().split())
t = []
for _ in range(n):
    b, e = map(int, input().split())
    t.append([min(b, e), -1])
    t.append([max(b, e), 1])
points = [int(i) for i in input().split()]
for i in range(len(points)):
    t.append([points[i], 0, i])
t = sorted(t)
cnt = 0
for i in t:
    if i[1] == 0:
        points[i[2]] = cnt
    cnt += -i[1]
print(*points)
