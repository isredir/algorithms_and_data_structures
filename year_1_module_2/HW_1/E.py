a = int(input())
b = int(input())
n = int(input())
m = int(input())
min1 = n + (n - 1) * a
max1 = min1 + 2 * a
min2 = m + (m - 1) * b
max2 = min2 + 2 * b
if min2 > max1 or min1 > max2:
    print(-1)
elif min1 <= min2 and max1 >= max2:
    print(min2, max2)
elif min1 > min2 and max1 >= max2:
    print(min1, max2)
elif min1 <= min2 and max1 < max2:
    print(min2, max1)
elif min1 > min2 and max1 < max2:
    print(min1, max1)
