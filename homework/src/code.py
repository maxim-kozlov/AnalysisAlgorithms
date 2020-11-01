for i in range(m):
    for j in range(1, n, 2):
        row[i] -= matr_a[i][j] * matr_a[i][j - 1]
for j in range(q):
    for i in range(1, n, 2):
        col[j] -= matr_b[i][j] * matr_b[i - 1][j]
for i in range(m):
    for j in range(q):
        matr_c[i][j] = row[i] + col[j]
        for k in range(1, n, 2):
            matr_c[i][j] += (matr_a[i][k - 1] + matr_b[k][j]) * (matr_a[i][k] + matr_b[k-1][j])
if n % 2:
    for i in range(m):
        for j in range(q):
            matr_c[i][j] += matr_a[i][n - 1] * matr_b[n - 1][j]