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


n = int(input())
a = [int(i) for i in input().split()]
m = int(input())
b = [int(i) for i in input().split()]
print(*merge(a, b))
