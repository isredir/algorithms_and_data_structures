with open('input.txt') as f:
    s = f.readlines()
letters = {}
maxCount = 0
for i in ''.join(s):
    if i != ' ' and i != '\n':
        if i not in letters.keys():
            letters[i] = 0
        letters[i] += 1
        maxCount = max(maxCount, letters[i])
gistogram = []
alphabet = sorted(letters.keys())
for i in range(maxCount, 0, -1):
    st = ''
    for j in alphabet:
        if letters[j] >= i:
            st += '#'
        else:
            st += ' '
    print(st)
print(*alphabet, sep='')
