for _ in range(int(input())):
    str = [float(i) for i in input().split()]
    k = int(str[0])
    a = str[1:]
    _a = sorted(a, reverse=True)
    s = []
    res = 1
    for i in range(k):
        if _a[len(_a) - 1] in s and s[len(s) - 1] != _a[len(_a) - 1]:
            res = 0
        if a[i] == _a[len(_a) - 1]:
            _a.pop()
        else:
            while len(s) > 0:
                if s[len(s) - 1] == _a[len(_a) - 1]:
                    s.pop()
                    _a.pop()
                else:
                    break
            s.append(a[i])
    while len(s) > 0:
        if s[len(s) - 1] == _a[len(_a) - 1]:
            s.pop()
            _a.pop()
        else:
            break
    if s:
        res = 0
    print(res)
