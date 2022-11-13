x1, y1, x2, y2 = [int(i) for i in input().split()]
l1 = max(x1, y1)
w1 = min(x1, y1)
l2 = max(x2, y2)
w2 = min(x2, y2)
minArea = max(l1, w2) * (w1 + l2)
minL, minW = max(l1, w2), (w1 + l2)
if max(l1, l2) * (w1 + w2) < minArea:
    minArea = max(l1, l2) * (w1 + w2)
    minL = max(l1, l2)
    minW = (w1 + w2)
if max(w1, w2) * (l1 + l2) < minArea:
    minArea = max(w1, w2) * (l1 + l2)
    minL = max(w1, w2)
    minW = (l1 + l2)
if max(w1, l2) * (l1 + w2) < minArea:
    minArea = max(w1, l2) * (l1 + w2)
    minL = max(w1, l2)
    minW = (l1 + w2)
print(minL, minW)
