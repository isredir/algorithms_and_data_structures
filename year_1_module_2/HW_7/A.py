n = int(input())
f = [0, 2, 4, 7]
for i in range(4, n + 1):
    f.append(f[i - 1] + f[i - 2] + f[i - 3])
print(f[n])
