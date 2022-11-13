n = int(input())
a = [int(i) for i in input().split()]
ok = False
for i in range(len(a) - 1):
    if a[i + 1] - a[i] > 1:
        ok = True
if a[0] - a[len(a) - 1] > 1:
    ok = True
if not ok:
    ok = True
while True:
    count = 0
    for i in range(len(a) - 1):
        if a[i + 1] - a[i] > 1:
            print(a[i + 1], a[i])
            ok = True
            count += 1
            a[i], a[i + 1] = a[i + 1], a[i]
    if a[0] - a[len(a) - 1] > 1:
        print(a[0], a[len(a) - 1])
        ok = True
        count += 1
        a[0], a[len(a) - 1] = a[len(a) - 1], a[0]
    if count == 0:
        break
if ok:
    print(0)
else:
    print(-1)
