n, k = map(int, input().split())
f = [0, 1]
for i in range(2, n + 1):
    s = 0
    j = i - 1
    while j >= i - k and j >= 1:
        s += f[j]
        j -= 1
    f.append(s)
print(f[n])
