def br(str):
    s = []
    for i in str:
        if i == ')':
            if len(s) != 0 and s[len(s) - 1] == '(':
                s.pop()
            else:
                return 'no'
        elif i == ']':
            if len(s) != 0 and s[len(s) - 1] == '[':
                s.pop()
            else:
                return 'no'
        elif i == '}':
            if len(s) != 0 and s[len(s) - 1] == '{':
                s.pop()
            else:
                return 'no'
        else:
            s.append(i)
    if len(s) == 0:
        return 'yes'
    else:
        return 'no'


print(br(input()))
