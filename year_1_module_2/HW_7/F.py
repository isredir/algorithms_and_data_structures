def f(board, n, m, i, j):
    if 0 <= i < n and 0 <= j < m:
        if board[i][j] == -1:
            board[i][j] = f(board, n, m, i - 2, j - 1) + \
                          f(board, n, m, i - 2, j + 1) + \
                          f(board, n, m, i - 1, j - 2) + \
                          f(board, n, m, i + 1, j - 2)
    else:
        return 0
    return board[i][j]


n, m = map(int, input().split())
board = []
for _ in range(n):
    board.append([-1] * m)
board[0][0] = 1
print(f(board, n, m, n - 1, m - 1))
