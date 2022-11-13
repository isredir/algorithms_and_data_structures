n, w, l = map(int, input().split())
t = []
for i in range(n):
    x1, y1, z1, x2, y2, z2 = map(int, input().split())
    area = (x2 - x1) * (y2 - y1)
    t.append([z1, 1, area, i + 1])
    t.append([z2, -1, area, i + 1])
t = sorted(t)
res = 10**6
cnt = 0
sumArea = 0
nums = set()
res_nums = []
for i in t:
    if i[1] == -1:
        cnt -= 1
        sumArea -= i[2]
        nums.remove(i[3])
    else:
        cnt += 1
        sumArea += i[2]
        nums.add(i[3])
    if sumArea == w * l:
        if cnt < res:
            res = cnt
            res_nums = list(nums)
if res != 10**6:
    print('YES')
    print(res)
    print(*sorted(res_nums))
else:
    print('NO')
