n, k = [int(i) for i in input().split()]
s = input()
letters = {}
for i in range(ord('a'), ord('z') + 1):
    letters[chr(i)] = 0
r, l = 0, 0
res_r, res_l = 0, 0
while r < n and l < n:
    if letters[s[r]] < k:
        if r - l > res_r - res_l:
            res_r, res_l = r, l
        letters[s[r]] += 1
        r += 1
    else:
        letters[s[l]] -= 1
        l += 1
print(res_r - res_l + 1, res_l + 1)
