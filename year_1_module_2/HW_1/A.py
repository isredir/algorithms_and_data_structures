troom, tcond = [int(i) for i in input().split()]
mode = input()
if mode == 'freeze':
    if tcond > troom:
        print(troom)
    else:
        print(tcond)
elif mode == 'heat':
    if tcond < troom:
        print(troom)
    else:
        print(tcond)
elif mode == 'auto':
    print(tcond)
elif mode == 'fan':
    print(troom)
