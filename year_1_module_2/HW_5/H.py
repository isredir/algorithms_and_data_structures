g, n = [int(i) for i in input().split()]
w = input()
word = {}
currWord = {}
for i in range(ord('a'), ord('z') + 1):
    word[chr(i)] = 0
    currWord[chr(i)] = 0
for i in range(ord('A'), ord('Z') + 1):
    word[chr(i)] = 0
    currWord[chr(i)] = 0
for i in w:
    word[i] += 1
s = input()
err = 0
res = 0
for i in range(g):
    currWord[s[i]] += 1
for i in currWord.keys():
    err += abs(currWord[i] - word[i])
if err == 0:
    res += 1
for i in range(g, n):
    old = s[i - g]
    new = s[i]
    err -= abs(word[old] - currWord[old])
    err -= abs(word[new] - currWord[new])
    currWord[old] -= 1
    currWord[new] += 1
    err += abs(word[old] - currWord[old])
    err += abs(word[new] - currWord[new])
    if err == 0:
        res += 1
print(res)
