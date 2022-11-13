sDigits = {}
kDigits = {}
for i in '0123456789':
    sDigits[i] = 0
    kDigits[i] = 0
sasha = input()
kate = input()
for i in sasha:
    sDigits[i] += 1
for i in kate:
    kDigits[i] += 1
res = ''
for i in '9876543210':
    if i == '0' and res == '' and sDigits[i] > 0 and kDigits[i] > 0:
        res += '0'
    else:
        for _ in range(min(sDigits[i], kDigits[i])):
            res += i
if res:
    print(res)
else:
    print(-1)
