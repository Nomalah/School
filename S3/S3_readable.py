def main():
    N, M, K = [int(x) for x in input().split()]

    song = []

    remGoodSampleCnt = K
    nextToAdd = 1
    while nextToAdd <= M and N <= remGoodSampleCnt:
        song.append(nextToAdd)
        remGoodSampleCnt -= len(song)
        nextToAdd += 1

    nextIndexToCheck = 0
    while len(song) < N:
        if remGoodSampleCnt == N - len(song):
            return song + [song[-1]] * (N - len(song))

        if nextIndexToCheck == len(song):
            return [-1]

        if N - nextIndexToCheck - 1 <= remGoodSampleCnt:
            remGoodSampleCnt -= len(song) - nextIndexToCheck
            song.append(song[nextIndexToCheck])
        nextIndexToCheck += 1


    if remGoodSampleCnt != 0:
        return [-1]
    else:
        return song

if __name__ == "__main__":
    print(" ".join(map(str, main())))