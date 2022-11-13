queue = []
size = 0
i = 0
while True:
    str = input().split()
    if str[0] == 'push':
        queue.append(str[1])
        size += 1
        print('ok')
    elif str[0] == 'pop':
        if size == 0:
            print('error')
        else:
            print(queue[i])
            i += 1
            size -= 1
    elif str[0] == 'front':
        if size == 0:
            print('error')
        else:
            print(queue[i])
    elif str[0] == 'size':
        print(size)
    elif str[0] == 'clear':
        queue = []
        i = 0
        size = 0
        print('ok')
    elif str[0] == 'exit':
        print('bye')
        break
