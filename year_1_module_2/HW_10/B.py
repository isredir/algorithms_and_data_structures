def get_hash(string):
    result = 0
    for char in string:
        result = (result * 18 + ord(char)) % 128
    return result


s = [''] * 13
s[0] = 'a'
for i in range(1, 13):
    st = ''
    for j in s[i - 1]:
        if j == 'p':
            st += 'a'
        else:
            st += 'p'
    s[i] = s[i - 1] + st
strings = set()
k = 1
s1 = s[8]
res = []
for i in range(1, 20):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[8]
for i in range(1, 18):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[8]
for i in range(1, 16):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[9] + s[8]
for i in range(1, 14):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[9] + s[9] + s[8]
for i in range(1, 12):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[9] + s[9] + s[9] + s[8]
for i in range(1, 10):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[8]
for i in range(1, 8):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[8]
for i in range(1, 6):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[8]
for i in range(1, 4):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[9] + s[8]
for i in range(1, 2):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[10] + s[8]
for i in range(1, 16):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[10] * 2 + s[8]
for i in range(1, 12):
    strings.add(s1)
    s1 += s[8]
    k += 1
s1 = s[10] * 3 + s[8]
for i in range(1, 3):
    strings.add(s1)
    s1 += s[8]
    k += 1
n = int(input())
j = 1
for i in strings:
    print(i)
    j += 1
    if j == n + 1:
        break
