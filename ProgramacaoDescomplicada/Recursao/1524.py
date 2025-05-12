while True:
    try:
        n, k = list(map(int, input().split()))
        l = list(map(int, input().split()))
        l.insert(0, 0)
        l.sort()
        buracos = []
        for i in range(n-1):
            buracos.append(l[i+1] - l[i])
        buracos.sort(reverse=True)
        ans = l[-1] - sum(buracos[0: k-1])
        print(ans)

    except EOFError:
        break

    