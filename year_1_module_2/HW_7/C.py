n = int(input())
f = [0, 0]
prev = []
for i in range(2, n + 1):
    prev1, prev2, prev3 = 10**9, 10**9, 10**9
    if i % 2 == 0:
        prev2 = f[i // 2]
    if i % 3 == 0:
        prev3 = f[i // 3]
    prev1 = f[i - 1]
    f.append(min(prev1, prev2, prev3) + 1)
print(f[n])
prev = []
i = n
while i > 0:
    prev.append(i)
    prev1, prev2, prev3 = 10 ** 9, 10 ** 9, 10 ** 9
    if i % 2 == 0:
        prev2 = f[i // 2]
    if i % 3 == 0:
        prev3 = f[i // 3]
    prev1 = f[i - 1]
    m = min(prev1, prev2, prev3)
    if prev1 == m:
        i -= 1
    elif prev2 == m:
        i //= 2
    elif prev3 == m:
        i //= 3
print(*reversed(prev))
