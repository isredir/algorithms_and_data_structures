def srt(i):
    return i[0]


n = int(input())
a = [[0, 0, 0]]
for i in range(n):
    h, l = map(int, input().split())
    a.append([l + h, h, l, i + 1])
a.pop(0)
a.sort(key=srt)
h = int(input())
p = 0
for i in a:
    p += i[1]
ans = []
dp = [[-1] * (n + 1)]
for i in range(n):
    dp.append([-1] * (n + 1))
dp[0][0] = p
for i in range(1, n + 1):
    dp[i][0] = p
    for j in range(1, n + 1):
        if dp[i - 1][j - 1] + a[i - 1][2] >= h:
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] - a[i - 1][1])
        else:
            dp[i][j] = dp[i - 1][j]
m = 0
for i in range(n + 1):
    if dp[n][i] != -1:
        m = i
for i in range(n, 0, -1):
    if dp[i - 1][m] != dp[i][m]:
        ans.append(a[i - 1][3])
        m -= 1
print(len(ans))
print(*ans)
