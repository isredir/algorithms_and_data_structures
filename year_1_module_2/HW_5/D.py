n = int(input())
letters = {}
for i in range(ord('A'), ord('Z') + 1):
    letters[chr(i)] = 0
for i in input():
    letters[i] += 1
minLetter = chr(ord('Z') + 1)
for i in range(ord('A'), ord('Z') + 1):
    if letters[chr(i)] % 2 != 0:
        if chr(i) < minLetter:
            minLetter = chr(i)
if minLetter == chr(ord('Z') + 1):
    minLetter = ''
res = ''
for i in range(ord('A'), ord('Z') + 1):
    for _ in range(letters[chr(i)] // 2):
        res += chr(i)
res += minLetter
for i in range(ord('Z'), ord('A') - 1, -1):
    for _ in range(letters[chr(i)] // 2):
        res += chr(i)
print(res)
