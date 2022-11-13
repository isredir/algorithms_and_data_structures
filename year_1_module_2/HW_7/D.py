n, m = map(int, input().split())
camp = [[10**9] * (m + 1)]
for i in range(1, n + 1):
    camp.append([10**9])
    camp[i] += [int(i) for i in input().split()]
for i in range(1, n + 1):
    for j in range(1, m + 1):
        if not i == j == 1:
            camp[i][j] = min(camp[i - 1][j], camp[i][j - 1]) + camp[i][j]
print(camp[n][m])
path = []
i, j = n, m
while i > 0 and j > 0:
    path.append([i, j])
    if camp[i - 1][j] < camp[i][j - 1]:
        i -= 1
    else:
        j -= 1
print(len(path))
for i in range(len(path) - 1, -1, -1):
    print(*path[i])
