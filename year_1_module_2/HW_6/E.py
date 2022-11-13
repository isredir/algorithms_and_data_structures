k = int(input())
s = input()
r = 0
res = 0
for l in range(len(s)):
    r = max(r, l + k)
    while r < len(s) and s[r - k] == s[r]:
        r += 1
    res += r - l - k
print(res)
