m = int(input())
n = 3
a = [int(i) for i in input().split()]
arr = [0] * (m + 1)
arr[0] = 1
maxWeight = 0
for i in range(n):
    for j in range(m):
        if j - a[i] >= 0:
            if arr[j - a[i]] == 1:
                arr[j] = 1
                maxWeight = max(maxWeight, j)
print(sum(arr))
