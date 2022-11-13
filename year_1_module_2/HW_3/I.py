n1 = int(input())
a = sorted([int(i) for i in input().split()])
n2 = int(input())
b = sorted([int(i) for i in input().split()])
n3 = int(input())
c = sorted([int(i) for i in input().split()])
n4 = int(input())
d = sorted([int(i) for i in input().split()])
i1, i2, i3, i4 = 0, 0, 0, 0
Min = min(a[0], b[0], c[0], d[0])
Max = max(a[0], b[0], c[0], d[0])
md = abs(Max - Min)
m1, m2, m3, m4 = i1, i2, i3, i4
while i1 < n1 and i2 < n2 and i3 < n3 and i4 < n4:
    Min = min(a[i1], b[i2], c[i3], d[i4])
    Max = max(a[i1], b[i2], c[i3], d[i4])
    dif = abs(Max - Min)
    if dif < md:
        md = dif
        m1, m2, m3, m4 = i1, i2, i3, i4
    if dif < 1:
        break
    while i1 < n1 and Min == a[i1]:
        i1 += 1
    while i2 < n2 and Min == b[i2]:
        i2 += 1
    while i3 < n3 and Min == c[i3]:
        i3 += 1
    while i4 < n4 and Min == d[i4]:
        i4 += 1
print(a[m1], b[m2], c[m3], d[m4])
