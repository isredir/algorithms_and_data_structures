def br(s):
    if s[0] != '<':
        return 0
    if s[len(s) - 1] != '>':
        return len(s) - 1
    stack = []
    for i in range(len(s)):
        if s[i] == '<' and s[i - 1] != '>':
            return i - 1
        if s[i] == '>' and s[i - 1] in ['>', '<', '/']:
            return i - 1
        if s[i] == '/' and s[i - 1] != '<':
            return i - 1
        if 'a' <= s[i] <= 'z':
            if s[i - 1] == '>':
                return i - 1
            if s[i - 1] == '<':
                tag = s[i]
            elif s[i - 1] == '/':
                tag = '/' + s[i]
            else:
                tag += s[i]
        if s[i] == '>' and 'a' <= s[i - 1] <= 'z':
            if tag[0] == '/':
                if len(stack) > 0 and stack[len(stack) - 1] == tag[1:]:
                    stack.pop()
                    if len(stack) > 0:
                        back -= (2 + len(stack[len(stack) - 1]))
                elif len(stack) > 0:
                    index = 0
                    for k in range(1, len(tag)):
                        if k < len(stack[len(stack) - 1]):
                            if tag[k] != stack[len(stack) - 1][k - 1]:
                                index = k
                                break
                    return [i - len(tag), i - (len(tag) - index), back]
                else:
                    return i - len(tag)
            else:
                stack.append(tag)
                back = i - len(tag)
    if len(stack) == 0:
        return -1
    else:
        return back


s = input()
lst = [i for i in s]
index = br(lst)
char = [j for j in range(ord('a'), ord('z') + 1)]
char += [ord('<'), ord('>'), ord('/')]
res = False
while True:
    for j in char:
        if isinstance(index, int):
            x = lst[index]
            lst[index] = chr(j)
            if br(lst) == -1:
                print(*lst, sep='')
                res = True
                break
            lst[index] = x
        else:
            for i in range(3):
                if res:
                    break
                x = lst[index[i]]
                lst[index[i]] = chr(j)
                if br(lst) == -1:
                    print(*lst, sep='')
                    res = True
                    break
                lst[index[i]] = x
        if res:
            break
    if res:
        break
    else:
        if isinstance(index, int):
            index += 1
        else:
            index = min(index)
