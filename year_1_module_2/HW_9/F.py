n, m = map(int, input().split())
a = [int(i) for i in input().split()]
arr = [0] * (m + 1)
arr[0] = 1
maxWeight = 0
for i in range(n):
    for j in range(m, -1, -1):
        if j - a[i] < 0:
            break
        else:
            if arr[j - a[i]] == 1:
                arr[j] = 1
                maxWeight = max(maxWeight, j)
print(maxWeight)
