import math

def main():
    N, M, K = [int(x) for x in input().split()]
    
    if K < N:
        return [-1]
    
    song = list(range(1, min(M, math.floor(math.sqrt(1-8*N+8*K)/2 - 1/2) + 1) + 1))
    K -= len(song) * (len(song) + 1) // 2

    while len(song) % M == 0:
        song += list(range(1, min(M, K // M) + 1))
        print(song)
        K -= song[-1] * M
    

    nextToCheckIndex = 0
    while len(song) < N:
        if K == N - len(song):
            return song + [song[-1]] * (N - len(song))

        if nextToCheckIndex == len(song):
            return [-1]
        
        if N - nextToCheckIndex - 1 <= K:
            K -= len(song) - nextToCheckIndex
            song.append(song[nextToCheckIndex])
        nextToCheckIndex += 1


    if remGoodSampleCnt != 0:
        return [-1]
    else:
        return song

if __name__ == "__main__":
    print(" ".join(map(str, main())))