def selection(arr):
    for i in range(len(arr) - 1, 0, -1):
        m = i
        for j in range(i):
            if arr[j] > arr[m]:
                m = j
        arr[m], arr[i] = arr[i], arr[m]
    return arr


n = int(input())
if n > 0:
    print(*selection([int(i) for i in input().split()]))
