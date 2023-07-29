import math

def main():
    N, M, K = map(int, input().split())
    
    if K < N:
        return ["-1"]
    if N == K:
        return ["1"] * N
    if M == 1:
        return ["-1"]

    maxVal = int((math.sqrt(1-8*N+8*K) + 1) // 2)

    if maxVal < M:
        K -= maxVal * (maxVal + 1) // 2
        return list(map(str, range(1, maxVal + 1))) + [str(N-K)] * (N - maxVal)
    
    
    song = list(map(str, range(1, M + 1)))
    K -= M * (M + 1) // 2 

    nextToCheckIndex = 0
    while len(song) < N:
        if N - nextToCheckIndex - 1 <= K:
            if K == N - len(song):
                return song + [song[-1]] * (N - len(song))
            if nextToCheckIndex >= len(song):
                return ["-1"]
            K -= M
            song.append(song[nextToCheckIndex])
            nextToCheckIndex += 1
        else:
            nextToCheckIndex = N - K - 1
            if nextToCheckIndex >= len(song):
                return ["-1"]
            return song + [song[nextToCheckIndex]] * (N - len(song))

    if K != 0:
        return ["-1"]
    else:
        return song

if __name__ == "__main__":
    print(" ".join(main()))