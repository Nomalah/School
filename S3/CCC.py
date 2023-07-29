N, M, K = map(int, input().split())

# check that K is valid
max = (N*(1+N))/2 - ((N-M)*(1+N-M))/2
if (K < N) or (K > max):
  print(-1)
else: 
  # determine L and x
  L = 1
  while K-(N-L) > 0:
    K -= N-L
    L += 1
  
  song = []
  # construct the first part of song containing x good samples of level L
  for i in range(L+K-1):
    song.append(i%L + 1)
  # construct the second part of the song that repeats the last L-1 notes of the first part
  postfix = [ song[-i] for i in range(L - 1, 0, -1)]
  for i in range(N - (L+K-1)):
    song.append(postfix[i%(L-1)])
  
  print(" ".join(map(str, song)))