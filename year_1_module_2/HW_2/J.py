from collections import deque
n = int(input())
d = deque()
for i in [int(i) for i in input().split()]:
    d.append(i)
q = int(input())
max_x = max(d)
pairs = []
count = 0
while d[0] != max_x:
    x, y = d[0], d[1]
    pairs.append([x, y])
    count += 1
    d.popleft()
    d.popleft()
    d.appendleft(max(x, y))
    d.append(min(x, y))
d.popleft()
for _ in range(q):
    k = int(input())
    if k <= count:
        print(*pairs[k - 1])
    else:
        print(max_x, d[(k - count) % (len(d)) - 1])
