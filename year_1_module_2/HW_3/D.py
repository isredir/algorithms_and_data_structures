def insert(arr):
    for i in range(len(arr)):
        x = arr[i]
        j = i
        swapped = False
        while j > 0 and arr[j - 1] > x:
            swapped = True
            arr[j] = arr[j - 1]
            j -= 1
        arr[j] = x
        if swapped:
            print(*arr)


n = int(input())
insert([int(i) for i in input().split()])
