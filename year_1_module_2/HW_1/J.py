def win(x):
    return a[0][0] == a[1][0] == a[2][0] == x or \
           a[0][1] == a[1][1] == a[2][1] == x or \
           a[0][2] == a[1][2] == a[2][2] == x or \
           a[0][0] == a[0][1] == a[0][2] == x or \
           a[1][0] == a[1][1] == a[1][2] == x or \
           a[2][0] == a[2][1] == a[2][2] == x or \
           a[0][0] == a[1][1] == a[2][2] == x or \
           a[0][2] == a[1][1] == a[2][0] == x

a = []
X, O, nothing = 0, 0, 0
for i in range(3):
    a.append([])
    for j in [int(x) for x in input().split()]:
        a[i].append(j)
        if j == 1:
            X += 1
        elif j == 2:
            O += 1
        else:
            nothing += 1
if X > O + 1 or O > X:
    print('NO')
elif win(1) and win(2):
    print('NO')
elif X == O == 3 and win(1):
    print('NO')
elif X == O + 1 == 4 and win(2):
    print('NO')
else:
    print('YES')
