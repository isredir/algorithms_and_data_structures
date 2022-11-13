def build_heap(arr, size, i):
    m = i
    if 2 * i + 1 < size and arr[2 * i + 1] > arr[m]:
        m = 2 * i + 1
    if 2 * i + 2 < size and arr[2 * i + 2] > arr[m]:
        m = 2 * i + 2
    if m != i:
        arr[i], arr[m] = arr[m], arr[i]
        build_heap(arr, size, m)


def heap_sort(arr):
    for i in range(len(arr), -1, -1):
        build_heap(arr, len(arr), i)
    for i in range(len(arr) - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        build_heap(arr, i, 0)


n = int(input())
arr = [int(i) for i in input().split()]
heap_sort(arr)
print(*arr)
