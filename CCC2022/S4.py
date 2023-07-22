def main():
    N, M, K = [int(x) for x in input().split()]
    if K < N:
        print(-1)
        return
    res = [False]

    a = K-N
    b = N - a - 1
    if a >= N:
        print(-1)
        return

    last = False
    for i in range(a):
        last = not last
        res.append(last)

    res += [last] * b
    for o, i in zip(res, range(len(res))):
        if o:
            res[i] = "2"
        else:
            res[i] = "1"
    print(" ".join(res))

main()
