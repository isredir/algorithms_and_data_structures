class Heap:
    def __init__(self):
        self.lst = [10**6]
        self.size = 0

    def insert(self, k):
        self.lst.append(k)
        self.size += 1
        i = self.size
        while i // 2 > 0:
            if self.lst[i] > self.lst[i // 2]:
                self.lst[i], self.lst[i // 2] = \
                    self.lst[i // 2], self.lst[i]
            i //= 2

    def extract(self):
        x = self.lst[1]
        self.lst[1] = self.lst[self.size]
        self.size -= 1
        self.lst.pop()
        i = 1
        while i * 2 <= self.size:
            if 2 * i + 1 > self.size:
                j = 2 * i
            elif self.lst[2 * i] < self.lst[2 * i + 1]:
                j = 2 * i + 1
            else:
                j = 2 * i
            if self.lst[i] < self.lst[j]:
                self.lst[i], self.lst[j] = self.lst[j], self.lst[i]
            i = j
        return x


n = int(input())
heap = Heap()
for _ in range(n):
    s = input().split()
    if s[0] == '0':
        heap.insert(int(s[1]))
    else:
        print(heap.extract())
