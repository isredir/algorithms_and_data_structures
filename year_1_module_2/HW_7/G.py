n = int(input())
a = [int(i) for i in input().split()]
m = int(input())
b = [int(i) for i in input().split()]
dp = []
pr = 0
for i in range(n + 1):
    dp.append([0] * (m + 1))
for i in range(1, n + 1):
    for j in range(1, m + 1):
        if a[i - 1] != b[j - 1]:
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
        else:
            dp[i][j] = dp[i - 1][j - 1] + 1
path = [0] * (dp[n][m])
i, j, k = n, m, 0
while k < dp[n][m]:
    if a[i - 1] == b[j - 1]:
        path[k] = a[i - 1]
        j -= 1
        i -= 1
        k += 1
    else:
        if dp[i][j - 1] > dp[i - 1][j]:
            j -= 1
        else:
            i -= 1
print(*reversed(path))
