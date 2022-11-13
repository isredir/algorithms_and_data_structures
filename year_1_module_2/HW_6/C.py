n, m = [int(i) for i in input().split()]
d = [int(i) for i in input().split()]
cnt = 0
r = 0
for l in range(n):
    while r < n and d[r] - d[l] <= m:
        r += 1
    cnt += (n - r)
print(cnt)
