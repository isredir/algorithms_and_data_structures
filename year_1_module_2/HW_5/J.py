m = input()
f = input()
md = {}
fd = {}
for i in range(ord('a'), ord('z') + 1):
    md[chr(i)] = []
    fd[chr(i)] = []
for i in range(len(m)):
    md[m[i]].append(i)
for i in range(len(f)):
    fd[f[i]].append(i)
mPos = 0
fPos = 0
child = ''
for i in range(ord('z'), ord('a') - 1, -1):
    if md[chr(i)] and fd[chr(i)]:
        mCount = 0
        minM = 10**9
        for j in range(len(md[chr(i)])):
            if md[chr(i)][j] >= mPos:
                minM = min(minM, j)
                mCount += 1
        fCount = 0
        minF = 10**9
        for j in range(len(fd[chr(i)])):
            if fd[chr(i)][j] >= fPos:
                minF = min(minF, j)
                fCount += 1
        count = min(mCount, fCount)
        for j in range(count):
            child += chr(i)
        if minM != 10**9 and minF != 10**9:
            mPos = md[chr(i)][minM + count - 1]
            fPos = fd[chr(i)][minF + count - 1]
print(child)
