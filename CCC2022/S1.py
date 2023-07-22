combos = [0, 4, 5, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 26, 27, 31]

def main():
    N= int(input())
    if N < 20 and N in combos:
        print(1)
    else:
        for x in combos:
            if (N - x) % 20 == 0:
                print((N-x)//20 + 1)
                return
            

        print(0)
main()
