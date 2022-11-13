stack = []
while True:
    str = input().split()
    if str[0] == 'push':
        stack.append(str[1])
        print('ok')
    elif str[0] == 'pop':
        if len(stack) == 0:
            print('error')
        else:
            print(stack[len(stack) - 1])
            stack.pop()
    elif str[0] == 'back':
        if len(stack) == 0:
            print('error')
        else:
            print(stack[len(stack) - 1])
    elif str[0] == 'size':
        print(len(stack))
    elif str[0] == 'clear':
        stack = []
        print('ok')
    elif str[0] == 'exit':
        print('bye')
        break
