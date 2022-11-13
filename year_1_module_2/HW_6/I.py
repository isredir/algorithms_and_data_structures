n = int(input())
t = []
for _ in range(n):
    a, b = map(int, input().split())
    t.append([a, -1])
    t.append([b + a - 1, 1])
t = sorted(t)
res = 0
cnt = 0
for i in t:
    cnt += -i[1]
    res = max(res, cnt)
print(res)
