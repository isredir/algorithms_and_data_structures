n, k = map(int, input().split())
s = input()
cnt = 0
for i in range(n):
    x = 0
    j = 1
    if x <= k:
        cnt += 1
    while i - j >= 0 and i + j < n and x <= k:
        if s[i - j] != s[i + j]:
            x += 1
        if x <= k:
            cnt += 1
        j += 1
for i in range(n - 1):
    if s[i] == s[i + 1]:
        x = 0
    else:
        x = 1
    if x <= k:
        cnt += 1
    j = 1
    while i - j >= 0 and i + j + 1 < n and x <= k:
        if s[i - j] != s[i + j + 1]:
            x += 1
        if x <= k:
            cnt += 1
        j += 1
print(cnt)
