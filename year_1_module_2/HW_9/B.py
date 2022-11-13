n, k, s = map(int, input().split())
if n % k == 0:
    m = n
else:
    m = k * (n // k + 1)
arr = []
for i in range(k):
    arr.append([0] * k)
cnt = 0
for i in range(k):
    for j in range(k):
        if cnt < s:
            arr[i][j] = 1
            cnt += 1
res = []
for i in range(m):
    res.append([0] * m)
    for j in range(m):
        res[i][j] = arr[i % k][j % k]
for i in range(n):
    for j in range(n):
        print(res[i][j], end=' ')
    print('\n', end='')
