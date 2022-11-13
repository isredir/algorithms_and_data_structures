n, m = map(int, input().split())
t = []
for _ in range(m):
    b, e = map(int, input().split())
    t.append([b, 1])
    t.append([e, -1])
t = sorted(t)
cnt = 0
res = t[0][0]
for i in range(len(t)):
    if t[i][0] != t[0][0] and cnt == 0:
        if t[i][0] != t[i - 1][0]:
            res += t[i][0] - t[i - 1][0] - 1
    cnt += t[i][1]
res += n - t[len(t) - 1][0] - 1
print(res)
