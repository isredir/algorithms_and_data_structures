n = int(input())
arr = [int(i) for i in input().split()]
s, maxS = 0, 0
neg = 0
for i in range(n):
    s += arr[i]
    maxS = max(maxS, s)
    if s < 0:
        neg += 1
        s = 0
if neg == n:
    print(max(arr))
else:
    print(maxS)
