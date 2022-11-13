class Node:
    def __init__(self, next=None, prev=None, this=None):
        self.next = next
        self.prev = prev
        self.this = this


class DoubleLinkedList:
    def __init__(self, head=None, tail=None, length=0):
        self.head = head
        self.tail = tail
        self.length = length

    def pushback(self, x):
        if self.tail is None:
            node = Node(None, None, x)
            self.head = node
            self.tail = self.head
            self.length = 1
        else:
            node = Node(None, self.tail, x)
            self.tail.next = node
            self.tail = node
            self.length += 1

    def popback(self):
        try:
            if self.tail is None:
                raise Exception("empty")
            else:
                self.tail = self.tail.prev
                if self.tail is not None:
                    self.tail.next = None
                self.length -= 1
        except Exception as error:
            print('error')

    def pushfront(self, x):
        if self.head is None:
            node = Node(None, None, x)
            self.head = node
            self.tail = self.head
            self.length = 1
        else:
            node = Node(self.head, None, x)
            self.head.prev = node
            self.head = self.head.prev
            self.length += 1

    def popfront(self):
        try:
            if self.head is None:
                raise Exception("empty")
            else:
                self.head = self.head.next
                if self.head is not None:
                    self.head.prev = None
                self.length -= 1
        except Exception as error:
            print('error')

    def getsize(self):
        return self.length

    def front(self):
        return self.head.this

    def back(self):
        return self.tail.this

    def out(self):
        node = self.head
        for i in range(self.length):
            print(node.this, end=' ')
            node = node.next


q = DoubleLinkedList()
n, k = [int(i) for i in input().split()]
arr = [int(i) for i in input().split()]
if k == 1:
    print(*arr)
else:
    for i in range(k):
        while q.getsize() > 0:
            if arr[i] < q.back():
                q.popback()
            else:
                break
        q.pushback(arr[i])
    a = []
    x = q.front()
    a.append(x)
    for i in range(k, n):
        if q.front() == arr[i - k]:
            q.popfront()
        while q.getsize() > 0:
            if arr[i] < q.back():
                q.popback()
            else:
                break
        q.pushback(arr[i])
        x = q.front()
        a.append(x)
    print(*a)
