fib = set()
fib.add(1)
n = int(input())
a, b = 1, 1
for _ in range(n):
    x = int(input())
    if x > b:
        while x > b:
            a, b = b, a + b
            fib.add(b)
    if x in fib:
        print('Yes')
    else:
        print('No')
