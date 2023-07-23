var cursorlocation : int := 1
var x : array 1 .. 3 of int := init
    (32, 32, 64)
var y1 : array 1 .. 3 of int := init
    (572, 548, 560)
var y2 : array 1 .. 3 of int := init
    (540, 516, 528)
var y3 : array 1 .. 3 of int := init
    (508, 484, 496)
loop
    cls
    delay (50)
    Draw.Box (16, 16, 592, 592, 255)
    delay (50)
    Draw.Box (16, 464, 272, 592, 255)
    delay (50)
    Font.Draw ("Load Game", 74, 552, font (1), 255)
    delay (50)
    Font.Draw ("New Game", 74, 520, font (1), 255)
    delay (50)
    Font.Draw ("Controls", 74, 488, font (1), 255)
    delay (50)
    loop
	Draw.FillPolygon (x, y1, 3, (abs (min (cursorlocation - 2, 0))) * 255)
	Draw.FillPolygon (x, y2, 3, (round (- (cursorlocation / 2 - 1) ** 2 * 4 + 1)) * 255)
	Draw.FillPolygon (x, y3, 3, (abs (max (cursorlocation - 2, 0))) * 255)
	Input.KeyDown (chars)
	if chars (KEY_UP_ARROW) then
	    if cursorlocation - 1 ~= 0 then
		cursorlocation -= 1
		delay (200)
	    end if
	elsif chars (KEY_DOWN_ARROW) then
	    if cursorlocation + 1 ~= 4 then
		cursorlocation += 1
		delay (200)
	    end if
	elsif chars ('c') then
	    exit
	end if
    end loop
    if cursorlocation = 1 then
    elsif cursorlocation = 2 then
	var stream : int
	var s : string
	open : stream, "SaveFile/SaveFile.t", get
	get : stream, s
	if s = "0" then
	    File.Copy ("SaveFile/DefaultSaveFile.t", "SaveFile/SaveFile.t")
	    exit
	else
	    cls
	    delay (50)
	    Draw.Box (16, 16, 592, 592, 255)
	    delay (50)
	    Draw.Box (16, 240, 336, 592, 255)
	    Font.Draw ("Are You Sure", 42, 552, font (1), 255)
	    delay (50)
	    Font.Draw ("You Want To", 42, 520, font (1), 255)
	    delay (50)
	    Font.Draw ("Overwrite the previous", 42, 552, font (1), 255)
	    delay (50)
	    Font.Draw ("Save File?", 42, 520, font (1), 255)
	    delay (50)
	    loop
		Input.KeyDown (chars)
		if chars ('c') then
		    File.Copy ("SaveFile/DefaultSaveFile.t", "SaveFile/SaveFile.t")
		    exit
		elsif chars ('x') then
		    exit
		end if
	    end loop
	end if
    elsif cursorlocation = 3 then
	cls
	delay (50)
	Draw.Box (16, 16, 592, 592, 255)
	delay (50)
	Draw.Box (16, 240, 336, 592, 255)
	delay (50)
	Font.Draw ("Interact/", 42, 552, font (1), 255)
	delay (50)
	Font.Draw ("Positive", 42, 520, font (1), 255)
	delay (50)
	Font.Draw ("Exit/", 42, 488, font (1), 255)
	delay (50)
	Font.Draw ("Negative", 42, 456, font (1), 255)
	delay (50)
	Font.Draw ("Run", 42, 424, font (1), 255)
	delay (50)
	Font.Draw ("Menu", 42, 392, font (1), 255)
	delay (50)
	Font.Draw ("Up", 42, 360, font (1), 255)
	delay (50)
	Font.Draw ("Down", 42, 328, font (1), 255)
	delay (50)
	Font.Draw ("Left", 42, 296, font (1), 255)
	delay (50)
	Font.Draw ("Right", 42, 264, font (1), 255)
	delay (50)
	Font.Draw ("C", 170, 552, font (1), 255)
	delay (50)
	Font.Draw ("X", 170, 488, font (1), 255)
	delay (50)
	Font.Draw ("Z", 170, 424, font (1), 255)
	delay (50)
	Font.Draw ("M", 170, 392, font (1), 255)
	delay (50)
	Font.Draw ("Up Arrow", 170, 360, font (1), 255)
	delay (50)
	Font.Draw ("Down Arrow", 170, 328, font (1), 255)
	delay (50)
	Font.Draw ("Left Arrow", 170, 296, font (1), 255)
	delay (50)
	Font.Draw ("Right Arrow", 170, 264, font (1), 255)
	delay (50)
	loop
	    Input.KeyDown (chars)
	    exit when chars ('x')
	end loop
    end if
end loop

