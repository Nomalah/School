setscreen ("graphics:640;640")
var pic : int := Pic.FileNew ("Poketest.bmp")
for x : 0 .. 19
    for y : 0 .. 19
	Pic.Draw (pic, x * 32, y * 32, picCopy)
    end for
end for

