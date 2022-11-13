def lower_bound(arr, x, i):
    if x > arr[len(arr) - 1][i]:
        return len(arr)
    l = 0
    r = len(arr) - 1
    while l < r:
        if x > arr[(r + l) // 2][i]:
            l = (r + l) // 2 + 1
        else:
            r = (r + l) // 2
    return l


n = int(input())
parties = []
summ = [0] * n
for i in range(n):
    a, b = [int(i) for i in input().split()]
    parties.append([a, b, i, 10**9])
s = sorted(parties)
summ[n - 1] = s[n - 1][0]
for i in range(n - 2, -1, -1):
    summ[i] = summ[i + 1] + s[i][0]
min_pay = 10**9
best_party = 0
max_vote = 0
for pos in range(len(s)):
    if s[pos][1] == -1:
        s[pos][3] = 10**9
    else:
        l, r = s[pos][0], 2*10**6
        resVot = 0
        while l <= r:
            d = (l + r) // 2
            i = lower_bound(s, d, 0)
            if i != n and d == s[pos][0]:
                i += 1
            if i != n:
                if d - s[pos][0] >= summ[i] - (n - i) * (d - 1):
                    resVot = d
                    r = d - 1
                else:
                    l = d + 1
            else:
                resVot = d
                r = d - 1
        s[pos][3] = resVot - s[pos][0] + s[pos][1]
        if s[pos][3] < min_pay:
            min_pay = s[pos][3]
            best_party = s[pos][2]
delta = min_pay - parties[best_party][1] + parties[best_party][0]
delta_pay = min_pay - parties[best_party][1]
for pos in range(n - 1, -1, -1):
    if s[pos][2] == best_party:
        break
    while s[pos][0] >= delta:
        s[pos][0] -= 1
        delta_pay -= 1
for pos in range(n - 1, -1, -1):
    if s[pos][2] != best_party:
        while s[pos][0] > 0 and delta_pay > 0:
            s[pos][0] -= 1
            delta_pay -= 1
parties[best_party][0] += (min_pay - parties[best_party][1])
print(min_pay)
print(best_party + 1)
for i in parties:
    print(i[0], end=' ')
