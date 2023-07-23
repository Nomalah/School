var chars : array char of boolean
var maingif : array 1 .. 32 of int
for i : 1 .. 32
    maingif (i) := Pic.Scale (Pic.FileNew ("Pictures/TitleScreen/TitleScreenGif/TitleGif" + intstr (i) + ".jpg"), 183, 156)
end for
var continuetogame : boolean := false
var startScreen : int := Pic.FileNew ("Pictures/TitleScreen/TitleScreen.bmp")
Music.PlayFileLoop ("OpeningTheme.mp3")
Pic.Draw (startScreen, 0, 0, picCopy)
loop
    for i : 1 .. 32
	Input.KeyDown (chars)
	continuetogame := chars ('c')
	exit when continuetogame
	Pic.Draw (maingif (i), 200, 160, picCopy)
	delay (50)
    end for
    exit when continuetogame
end loop
continuetogame := false
Music.PlayFileStop
%Music.PlayFileLoop ("MainTheme.mp3")

