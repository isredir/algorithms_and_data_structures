n, m = [int(i) for i in input().split()]
letters = {}
for _ in range(n):
    for i in input():
        if i not in letters.keys():
            letters[i] = 0
        letters[i] += 1
for _ in range(m):
    for i in input():
        letters[i] -= 1
res = ''
for i in letters.keys():
    for _ in range(letters[i]):
        res += i
print(res)
