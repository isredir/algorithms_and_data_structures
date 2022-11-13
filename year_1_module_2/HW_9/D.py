def srt(i):
    return i[0]


n = int(input())
a = [int(i) for i in input().split()]
plays = []
for i in range(n):
    plays.append([a[i], i])
t = []
for i in range(n):
    t.append([0] * n)
for i in range(n):
    plays.sort(key=srt)
    j = i + 1
    while j < n and plays[i][0] > 0:
        plays[i][0] -= 1
        plays[j][0] -= 1
        t[plays[i][1]][plays[j][1]] = 1
        t[plays[j][1]][plays[i][1]] = 1
        j += 1
    while j < n:
        plays[j][0] -= 2
        t[plays[i][1]][plays[j][1]] = 0
        t[plays[j][1]][plays[i][1]] = 2
        j += 1
for i in range(n):
    print(*t[i])
