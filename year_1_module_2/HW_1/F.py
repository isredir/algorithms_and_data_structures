n, i, j = [int(x) for x in input().split()]
print(min(abs(j - i) - 1, n - max(i, j) - 1 + min(i, j)))
