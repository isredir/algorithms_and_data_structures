n = int(input())
keys = [int(i) for i in input().split()]
k = int(input())
s = [int(i) for i in input().split()]
for i in s:
    keys[i - 1] -= 1
for i in keys:
    if i < 0:
        print('yes')
    else:
        print('no')
