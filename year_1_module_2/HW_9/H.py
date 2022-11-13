n, m = map(int, input().split())
w, c = [0], [0]
w += [int(i) for i in input().split()]
c += [int(i) for i in input().split()]
arr = []
for i in range(n + 1):
    arr.append([0] * (m + 1))
for i in range(1, n + 1):
    arr[i][0] = 0
    for j in range(1, m + 1):
        if j - w[i] < 0:
            arr[i][j] = arr[i - 1][j]
        else:
            arr[i][j] = max(arr[i - 1][j - w[i]] + c[i], arr[i - 1][j])


def print_answer(n, m):
    if arr[n][m] == 0:
        return
    elif arr[n - 1][m] == arr[n][m]:
        print_answer(n - 1, m)
    else:
        print_answer(n - 1, m - w[n])
        print(n)


print_answer(n, m)
