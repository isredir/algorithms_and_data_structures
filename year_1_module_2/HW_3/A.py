def selection(s):
    m = s.index(max(s))
    s[m], s[len(s) - 1] = s[len(s) - 1], s[m]
    return s


n = int(input())
if n > 0:
    print(*selection([int(i) for i in input().split()]))
