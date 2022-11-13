import random


def partition(arr, x, left, right):
    l, r = left, right
    while l <= r:
        while l < len(arr) and arr[l] < x:
            l += 1
        while r >= 0 and arr[r] > x:
            r -= 1
        if l <= r:
            arr[l], arr[r] = arr[r], arr[l]
            l += 1
            r -= 1
    return [l, r]


def quick_sort(arr, begin, end):
    if begin >= end:
        return
    x = random.choice(arr[begin:end + 1])
    l, r = partition(arr, x, begin, end)
    quick_sort(arr, begin, r)
    quick_sort(arr, l, end)


n = int(input())
arr = [int(i) for i in input().split()]
quick_sort(arr, 0, len(arr) - 1)
print(*arr)
