a = int(input())
b = int(input())
c = int(input())
if c < 0:
    print('NO SOLUTION')
elif a == 0 and c**2 - b == 0:
    print('MANY SOLUTIONS')
elif a == 0 and c**2 - b != 0:
    print('NO SOLUTION')
elif a != 0:
    if (c**2 - b) % a == 0:
        print((c**2 - b) // a)
    else:
        print('NO SOLUTION')
