def lower_bound(arr, x):
    if x > arr[len(arr) - 1]:
        return len(arr)
    l = 0
    r = len(arr) - 1
    while l < r:
        if x > arr[(r + l) // 2]:
            l = (r + l) // 2 + 1
        else:
            r = (r + l) // 2
    return l


def g(arr1, arr2, x):
    return lower_bound(arr1, x) + lower_bound(arr2, x) + 1


def f(arr1, arr2, x):
    if len(arr1) == 1:
        return min(arr1[0], arr2[0])
    l, r = 0, len(arr1) - 1
    while l < r:
        d = (l + r) // 2
        if g(arr1, arr2, arr1[d]) < x:
            l = d + 1
        else:
            r = d
    if x == g(arr1, arr2, arr1[l]):
        return arr1[l]
    l1, r1 = 0, len(arr2) - 1
    while l1 < r1:
        d1 = (l1 + r1) // 2
        if g(arr1, arr2, arr2[d1]) < x:
            l1 = d1 + 1
        else:
            r1 = d1
    if x == g(arr1, arr2, arr2[l1]):
        return arr2[l1]
    if l1 == 0:
        return arr1[l - 1]
    if l == 0:
        return arr2[l1 - 1]
    return max(arr1[l - 1], arr2[l1 - 1])


n, size = [int(i) for i in input().split()]
arr = []
for _ in range(n):
    x1, d1, a, c, m = [int(i) for i in input().split()]
    x = [x1]
    d = [d1]
    for j in range(1, size):
        d.append((a * d[j - 1] + c) % m)
        x.append(x[j - 1] + d[j - 1])
    arr.append(x)
for i in range(n):
    for j in range(i + 1, n):
        print(f(arr[i], arr[j], size))
