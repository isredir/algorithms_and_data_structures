stack = []
while True:
    str = input().split()
    if str[0] == 'push':
        stack.append(str[1])
        print('ok')
    elif str[0] == 'pop':
        print(stack[len(stack) - 1])
        stack.pop()
    elif str[0] == 'back':
        print(stack[len(stack) - 1])
    elif str[0] == 'size':
        print(len(stack))
    elif str[0] == 'clear':
        stack = []
        print('ok')
    elif str[0] == 'exit':
        print('bye')
        break
