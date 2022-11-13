n = int(input())
i = 0
num = 0
themes = {}
messages = [''] * (n + 1)
while num < n:
    x = input()
    if x == '0':
        num += 1
        theme = input()
        question = input()
        themes[theme] = 1
        messages[num] = theme
    elif x.isdigit():
        num += 1
        m = int(x)
        themes[messages[m]] += 1
        messages[num] = messages[m]
        respond = input()
maxCount = 0
maxTheme = ''
for i in themes.keys():
    if themes[i] > maxCount:
        maxCount = themes[i]
        maxTheme = i
print(maxTheme)
