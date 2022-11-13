n, m = map(int, input().split())
w = [int(i) for i in input().split()]
c = [int(i) for i in input().split()]
arr = [-1] * (m + 1)
arr[0] = 0
maxWeight = 0
for i in range(n):
    for j in range(m, -1, -1):
        if j - w[i] < 0:
            break
        else:
            if arr[j - w[i]] != -1:
                arr[j] = max(arr[j - w[i]] + c[i], arr[j])
print(max(arr))
