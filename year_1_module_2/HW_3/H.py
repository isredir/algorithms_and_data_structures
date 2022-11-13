n = int(input())
a = [int(i) for i in input().split()]
res = []
d = {}
for i in range(len(a)):
    d[a[i]] = i
    res.append(a[i])
res1 = []
for i in range(len(res)):
    if i == d[res[i]]:
        res1.append(res[i])
print(len(res1))
print(*res1)
