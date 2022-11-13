deque = []
size = 0
while True:
    s = input().split()
    if s[0] == 'push_front':
        print('ok')
        deque.insert(0, s[1])
        size += 1
    elif s[0] == 'push_back':
        print('ok')
        deque.append(s[1])
        size += 1
    elif s[0] == 'pop_front':
        if size == 0:
            print('error')
        else:
            print(deque.pop(0))
            size -= 1
    elif s[0] == 'pop_back':
        if size == 0:
            print('error')
        else:
            print(deque.pop(-1))
            size -= 1
    elif s[0] == 'front':
        if size == 0:
            print('error')
        else:
            print(deque[0])
    elif s[0] == 'back':
        if size == 0:
            print('error')
        else:
            print(deque[-1])
    elif s[0] == 'size':
        print(size)
    elif s[0] == 'clear':
        deque = []
        size = 0
        print('ok')
    elif s[0] == 'exit':
        print('bye')
        break
