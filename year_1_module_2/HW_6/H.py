n = int(input())
m = n
t = [0] * 1440
for _ in range(m):
    h1, m1, h2, m2 = map(int, input().split())
    t1 = 60 * h1 + m1
    t2 = 60 * h2 + m2
    if t1 >= t2:
        for i in range(t1, 1440):
            t[i] += 1
        for i in range(t2):
            t[i] += 1
    else:
        for i in range(t1, t2):
            t[i] += 1
res = 0
for i in t:
    if i == n:
        res += 1
print(res)
