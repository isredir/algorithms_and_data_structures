s = input()
dp = []
ans = []
for i in range(len(s)):
    dp.append([0] * len(s))
    ans.append([0] * len(s))
for r in range(len(s)):
    for l in range(r, -1, -1):
        if l == r:
            dp[l][r] = 1
        else:
            minS, minK = 10**9, -1
            if (s[l] == '(' and s[r] == ')') or \
                    (s[l] == '[' and s[r] == ']') or \
                    (s[l] == '{' and s[r] == '}'):
                minS = dp[l + 1][r - 1]
            for k in range(l, r):
                if dp[l][k] + dp[k + 1][r] < minS:
                    minS = dp[l][k] + dp[k + 1][r]
                    minK = k
            dp[l][r], ans[l][r] = minS, minK


def f(l, r):
    if dp[l][r] == r - l + 1:
        return
    if dp[l][r] == 0:
        print(s[l:r + 1], end='')
        return
    if ans[l][r] == -1:
        print(s[l], end='')
        f(l + 1, r - 1)
        print(s[r], end='')
        return
    f(l, ans[l][r])
    f(ans[l][r] + 1, r)


f(0, len(s) - 1)
