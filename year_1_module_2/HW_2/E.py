first = input().split()
second = input().split()
i = 0
while len(first) != 0 and len(second) != 0:
    i += 1
    x, y = first.pop(0), second.pop(0)
    if x > y and not (x == '9' and y == '0') or (x == '0' and y == '9'):
        first.append(x)
        first.append(y)
    else:
        second.append(x)
        second.append(y)
    if i == 10**6:
        print('botva')
        break
else:
    print('first' if first else 'second', i)
