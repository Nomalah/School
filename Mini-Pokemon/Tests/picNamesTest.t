var stream : int
open : stream,"ListOfPosPicNames.t",put
for i : 0 .. 255
    put:stream, chr(i),i:10
end for
close : stream
