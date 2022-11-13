n, m = map(int, input().split())
x = [int(i) for i in input().split()]
y = [int(i) for i in input().split()]
xx = []
yy = []
for i in range(n):
    xx.append([x[i], i])
for i in range(m):
    yy.append([y[i], i])
xx = sorted(xx)
yy = sorted(yy, reverse=True)
x = [0] * n
cnt = 0
for i in yy:
    j = len(xx) - 1
    while j >= 0 and xx[j][0] >= i[0]:
        xx.pop()
        j -= 1
    if j >= 0:
        cnt += 1
        x[xx[j][1]] = i[1] + 1
        xx.pop()
        j -= 1
print(cnt)
print(*x)
