def srt(i):
    return i[2]


m = int(input())
a = [int(i) for i in input().split()]
b = []
for i in range(30):
    b.append([i, a[i], 2**i/int(a[i])])
b.sort(key=srt)


def solve(arr, m):
    num = arr.pop(0)
    if m % num[1] == 0:
        return (m // num[1]) * (2**num[0])
    else:
        a = (m // num[1] + 1) * (2**num[0])
        if arr:
            b = solve(arr.copy(), m % num[1]) + (m // num[1]) * (2**num[0])
        else:
            b = a
        return a if a < b else b


print(solve(b, m))
