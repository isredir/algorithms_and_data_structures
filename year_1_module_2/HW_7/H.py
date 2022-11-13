n = int(input())
a = [int(i) for i in input().split()]
dp = [1] * n
for i in range(n):
    for j in range(i):
        if a[i] > a[j]:
            dp[i] = max(dp[i], dp[j] + 1)
path = []
m = max(dp)
for i in range(n - 1, -1, -1):
    if dp[i] == m:
        path.append(a[i])
        m -= 1
print(*reversed(path))
