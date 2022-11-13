def partition(arr, x, l, r):
    while l <= r:
        while l < len(arr) and arr[l] < x:
            l += 1
        while r >= 0 and arr[r] >= x:
            r -= 1
        if l <= r:
            arr[l], arr[r] = arr[r], arr[l]
            l += 1
            r -= 1
    return [l, len(arr) - l]


n = int(input())
arr = [int(i) for i in input().split()]
x = int(input())
print(*partition(arr, x, 0, len(arr) - 1), sep='\n')
