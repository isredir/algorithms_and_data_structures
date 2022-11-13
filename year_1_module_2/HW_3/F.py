def merge(a, b, c):
    left, mid, right = 0, 0, 0
    merged = [0] * (len(a) + len(b) + len(c))
    while left < len(a) and mid < len(b) and right < len(c):
        if min(a[left], b[mid], c[right]) == a[left]:
            merged[left + mid + right] = a[left]
            left += 1
        elif min(a[left], b[mid], c[right]) == b[mid]:
            merged[left + mid + right] = b[mid]
            mid += 1
        else:
            merged[left + mid + right] = c[right]
            right += 1
    while left < len(a) and mid < len(b):
        if min(a[left], b[mid]) == a[left]:
            merged[left + mid + right] = a[left]
            left += 1
        else:
            merged[left + mid + right] = b[mid]
            mid += 1
    while left < len(a) and right < len(c):
        if min(a[left], c[right]) == a[left]:
            merged[left + mid + right] = a[left]
            left += 1
        else:
            merged[left + mid + right] = c[right]
            right += 1
    while right < len(c) and mid < len(b):
        if min(c[right], b[mid]) == c[right]:
            merged[left + mid + right] = c[right]
            right += 1
        else:
            merged[left + mid + right] = b[mid]
            mid += 1
    for left in range(left, len(a)):
        merged[left + mid + right] = a[left]
    for mid in range(mid, len(b)):
        merged[left + mid + right] = b[mid]
    for right in range(right, len(c)):
        merged[left + mid + right] = c[right]
    return merged


n, m, k = input().split()
a = [int(i) for i in input().split()]
b = [int(i) for i in input().split()]
c = [int(i) for i in input().split()]
print(*merge(a, b, c))
