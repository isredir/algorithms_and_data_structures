d = {}
sides = 'NSWEUD'
for i in sides:
    d[i] = input()
a, b = input().split()
b = int(b)
dp = {}
for i in sides:
    dp[i] = [0] * (b + 1)
for j in range(1, b + 1):
    for i in sides:
        if j == 1:
            dp[i][j] = 1
        else:
            s = 0
            for k in d[i]:
                s += dp[k][j - 1]
            dp[i][j] = s + 1
print(dp[a][b])
