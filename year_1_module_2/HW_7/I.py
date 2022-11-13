def upper_bound(a, x):
    if x < a[0][1]:
        return 0
    l = 0
    r = len(a) - 1
    while l < r:
        if x < a[(r + l + 1) // 2][1]:
            r = (r + l + 1) // 2 - 1
        else:
            l = (r + l + 1) // 2
    return r + 1


n = int(input())
intervals = []
for _ in range(n):
    b, e, v = map(float, input().split())
    intervals.append([e, b, v])
intervals = sorted(intervals)
for i in intervals:
    i[0], i[1] = i[1], i[0]
p = [0] * n
for i in range(len(intervals)):
    p[i] = upper_bound(intervals, intervals[i][0])
opt = [0] * (n + 1)
for j in range(1, n + 1):
    opt[j] = max(intervals[j - 1][2] + opt[p[j - 1]], opt[j - 1])
print(opt[n])
