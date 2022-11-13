n = int(input())
peaks = []
for _ in range(n):
    x, y = [int(i) for i in input().split()]
    peaks.append(y)
rises = [peaks[0]] * n
for i in range(1, n):
    if peaks[i] - peaks[i - 1] > 0:
        rises[i] = rises[i - 1] + peaks[i] - peaks[i - 1]
    else:
        rises[i] = rises[i - 1]
rises_rev = [peaks[n - 1]] * n
for i in range(n - 2, -1, -1):
    if peaks[i] - peaks[i + 1] > 0:
        rises_rev[i] = rises_rev[i + 1] + peaks[i] - peaks[i + 1]
    else:
        rises_rev[i] = rises_rev[i + 1]
m = int(input())
for _ in range(m):
    a, b = [int(i) for i in input().split()]
    if b > a:
        print(rises[b - 1] - rises[a - 1])
    else:
        print(rises_rev[b - 1] - rises_rev[a - 1])
