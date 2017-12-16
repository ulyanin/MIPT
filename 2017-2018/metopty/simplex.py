from math import sin
import numpy as np
from scipy.optimize import linprog


def pivot(N, B, A, b, c, v, l, e):
    ## x_e - новая базисная переменная
    ## вычислим коэффициенты уравнения для нее
    newA = np.zeros_like(A)
    newb = np.zeros_like(b)
    newc = np.zeros_like(c)
    N.remove(e)
    B.remove(l)
    newb[e] = -b[l] / A[l][e]
    for j in N:
        newA[e][j] = -A[l][j] / A[l][e]
    newA[e][l] = 1 / A[l][e]

    ## вычислим коэффициенты оставшихся ограничений

    for i in B:
        newb[i] = b[i] + A[i][e] * newb[e]
        for j in N:
            newA[i][j] = A[i][j] + A[i][e] * newA[e][j]
        newA[i][l] = A[i][e] * newA[e][l]

    ## вычислим значения целевой функции

    newv = v + c[e] * newb[e]
    for j in N:
        newc[j] = c[j] + c[e] * newA[e][j]
    newc[l] = c[e] * newA[e][l]
    N.append(l)
    B.append(e)

    return N, B, newA, newb, newc, newv


def positive(c, N):
    for i in N:
        if c[i] > 0:
            return i
    return -1


def simplex_(N, B, A, b, c, v):
    e = positive(c, N)
    while e != -1:
        ## METHOD
        delta = np.ones_like(A[0]) * np.inf
        for i in B:
            if A[i][e] < 0:
                delta[i] = b[i] / -A[i][e]
        l = np.argmin(delta)
        ## METHOD
        if delta[l] == np.inf:
            return "Simplex is failed! No boundaries..."
        else:
            (N, B, A, b, c, v) = pivot(N, B, A, b, c, v, l, e)
        print(c)
        e = positive(c, N)
    return N, B, A, b, c, v


def first_phase(n, m, N, B, A, b, c, v, k):
    x_0_ind = len(c) - 1

    N, B, A, b, c, v = pivot(N, B, A, b, c, v, k, x_0_ind)
    N, B, A, b, c, v = simplex_(N, B, A, b, c, v)

    x_0 = c[-1]
    if x_0 <= 0:
        if x_0_ind in B:
            otherVariable = B[0] if B[0] != x_0_ind else B[-1]
            N, B, A, b, c, v = pivot(N, B, A, b, c, v, otherVariable, x_0_ind)

        # delete last column assotiated with x_0
        A = A[:-1, :-1]
        c = c[:-1]
        b = b[:-1]
        if x_0_ind in N:
            N.remove(x_0_ind)
        return N, B, A, b, c, v
    return None


def Initialize(n, m, A, b, c):
    v = 0
    k = np.argmin(b)
    if b[k] >= 0:
        return list(range(n)), list(range(n, n + m)), A, b, c, 0
    # add fictive variable x_0
    # add one column to A
    tmp_A = np.zeros((A.shape[0] + 1, A.shape[0] + 1))
    tmp_A[:-1, :-1] = A.copy()
    # column with 1 on the place of basis variables
    tmp_A[n:n+m, -1] = 1
    # c = -x_0
    tmp_c = np.zeros(len(c) + 1)
    tmp_c[-1] = -1
    N = list(range(n)) + [len(c)]
    B = list(range(n, n + m))
    tmp_b = np.append(b.copy(), [0])
    ret = first_phase(n + 1, m, N, B, tmp_A, tmp_b, tmp_c, 0, k)
    if ret is not None:
        tmp_N, tmp_B, tmp_A, tmp_b, tmp_c, tmp_v = ret
        for i in B:
            v += c[i] * tmp_b[i]
            for j in N:
                c[j] = c[j] + c[i] * tmp_A[i][j]

        return tmp_N, tmp_B, tmp_A, tmp_b, c, v
    raise ValueError


def Simplex(n, m, A, b, c):
    N, B, A, b, c, v = Initialize(n, m, A, b, c)
    N, B, A, b, c, v = simplex_(N, B, A, b, c, v)
    res = np.zeros(len(A[0]))
    for i in range(len(A[0])):
        if i in B:
            res[i] = b[i]
    print(v)
    return v, res


def TransformMatrix(A):
    n = A.shape[1]
    m = A.shape[0]

    res = np.zeros((n + m, n + m))
    res[n:n + m, :n] = -A
    return res


# A=np.array([[1, 1, 3], [2, 2, 5], [4, 1, 2]], dtype=float)
# b=np.array([0, 0, 0, 30, 24, 36], dtype=float)
# c=np.array([3, 1, 2, 0, 0, 0], dtype=float)
# A = TransformMatrix(A)
# print(*Simplex(3, 3, A, b, c))
# A = np.array([[-1, 1], [-1, 2], [0, 1]], dtype=float)
# b = np.array([0, 0, -1, -2, 1], dtype=float)
# c = np.array([-2, -1, 0, 0, 0], dtype=float)
# A = TransformMatrix(A)
# print(*Simplex(2, 3, A, b, c))

A = np.array([[2, -1], [1, -5]], dtype=float)
b = np.array([0, 0, 2, -4], dtype=float)
c = np.array([2, -1, 0, 0], dtype=float)
A = TransformMatrix(A)
print(*Simplex(2, 2, A, b, c))
