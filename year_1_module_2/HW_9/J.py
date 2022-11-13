def f1(arr, m):
    n = len(arr)
    res = [0] * (m + 1)
    res[0] = 1
    for i in range(1, n + 1):
        for j in range(m, -1, -1):
            if j - arr[i - 1][0] < 0:
                break
            else:
                if res[j - arr[i - 1][0]] == 1:
                    res[j] = 1
    return res


def f2(arr, m):
    n = len(arr)
    res = []
    for i in range(n + 1):
        res.append([0] * (m + 1))
    res[0][0] = 1
    for i in range(1, n + 1):
        for j in range(m, -1, -1):
            res[i][j] = res[i - 1][j]
            if j - arr[i - 1][0] >= 0:
                if res[i - 1][j - arr[i - 1][0]] == 1:
                    res[i][j] = 1
    if res[n][m] == 1:
        nums = []
        j = m
        for i in range(n, 0, -1):
            if j - arr[i - 1][0] >= 0 and res[i - 1][j - arr[i - 1][0]] == 1:
                j -= arr[i - 1][0]
                nums.append(arr[i - 1][1])
        return [True, nums]
    else:
        return [False]


n, k = map(int, input().split())
z = [[]]
w = [0]
for i in range(n):
    l, c = map(int, input().split())
    if c >= len(z):
        while c >= len(z):
            w.append(0)
            z.append([])
    z[c].append([l, i + 1])
    w[c] += l
maxW = max(w)
res = []
for i in range(len(z)):
    res.append(f1(z[i], maxW))
flag = False
for v in range(1, maxW):
    can = True
    ans = [0] * len(w)
    for i in range(1, len(w)):
        if res[i][v] == 1:
            can = True
        else:
            can = False
            break
    if can:
        for i in range(1, len(w)):
            ans[i] = f2(z[i], v)[1]
        flag = True
        print('YES')
        for i in range(1, len(ans)):
            print(*ans[i], end=' ')
        break
if not flag:
    print('NO')
