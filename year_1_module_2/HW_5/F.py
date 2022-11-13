n = int(input())
arr = []
for _ in range(n):
    x = input()
    arr.append(x)
print('Initial array:')
print(*arr, sep=', ')
buckets = {}
for i in range(len(arr[0]) - 1, -1, -1):
    for j in range(10):
        buckets[j] = []
    for s in arr:
        digit = s[i]
        buckets[int(digit)].append(s)
    arr = []
    for j in range(10):
        for k in buckets[j]:
            arr.append(k)
    print('**********')
    print('Phase', len(arr[0]) - i)
    for j in range(10):
        if buckets[j]:
            print('Bucket ', j, ':', sep='', end=' ')
            print(*buckets[j], sep=', ')
        else:
            print('Bucket ', j, ':', ' empty', sep='')
print('**********')
print('Sorted array:')
print(*arr, sep=', ')
