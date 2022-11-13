n, m = map(int, input().split())
board = []
for _ in range(n):
    board.append([0] * m)
board[0][0] = 1
for i in range(n):
    for j in range(m):
        if i == 1 and j > 1:
            board[i][j] += board[i - 1][j - 2]
        elif j == 1 and i > 1:
            board[i][j] += board[i - 2][j - 1]
        elif j > 1 and i > 1:
            board[i][j] += board[i - 2][j - 1] + board[i - 1][j - 2]
print(board[n - 1][m - 1])
