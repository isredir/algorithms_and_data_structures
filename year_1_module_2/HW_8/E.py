l, n = map(int, input().split())
a = [0]
a += [int(i) for i in input().split()]
a.append(l)
dp = []
for i in range(n + 2):
    dp.append([0] * (n + 2))
for r in range(1, n + 2):
    for l in range(r - 2, -1, -1):
        dp[l][r] = 10**9
        for k in range(l + 1, r):
            dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r])
        dp[l][r] += a[r] - a[l]
print(dp[0][n + 1])
