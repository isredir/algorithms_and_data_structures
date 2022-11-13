m, n = map(int, input().split())
dp = [[1] * (m + 1), [1] * (m + 1)]
for i in range(2, n + 1):
    dp.append([0] * (m + 1))
    for j in range(1, m + 1):
        s = 0
        for k in range(1, j):
            s += 2 * dp[i - 1][k]
        dp[i][j] = s + dp[i - 1][j]
print(dp[n][m])
