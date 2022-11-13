def merge(a, b):
    left, right = 0, 0
    merged = [0] * (len(a) + len(b))
    while left < len(a) and right < len(b):
        if a[left] <= b[right]:
            merged[left + right] = a[left]
            left += 1
        else:
            merged[left + right] = b[right]
            right += 1
    for left in range(left, len(a)):
        merged[left + right] = a[left]
    for right in range(right, len(b)):
        merged[left + right] = b[right]
    return merged


def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    a, b = merge_sort(arr[:(len(arr) // 2)]), merge_sort(arr[(len(arr) // 2):])
    return merge(a, b)


n = input()
a = [int(i) for i in input().split()]
print(*merge_sort(a))
