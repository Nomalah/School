var window : int := Window.Open ("position:top;right,graphics:608;608,nocursor")
var font : array 1 .. 1 of int
font (1) := Font.New ("serif:22")
include "TitleScreen.t"
include "MainMenu.t"
var tiles : array 0 .. 57 of int
var characters : array 1 .. 16 of int
for character_num : 1 .. 12
    characters (character_num) := Pic.Scale (Pic.FileNew ("Pictures/Characters/" + intstr (character_num) + ".bmp"), 32, 32)
end for
for tile_num : 0 .. 57
    tiles (tile_num) := Pic.FileNew ("Pictures/Tiles/" + chr (tile_num + 65) + ".bmp")
end for
var picture : int
var map : array 1 .. 100, 1 .. 100 of int
var num_of_warp_points : int
var num_of_txt_objects : int
var num_of_interactive_objects : int
var interactive_objects : flexible array 0 .. 0, 1 .. 4 of int
var txt_objects : flexible array 0 .. 0, 1 .. 4 of int
var map_Warp_points : flexible array 0 .. 0, 1 .. 5 of int
proc load_Cur_Map (mapNum : int)
    var stream : int
    var s : string
    var map_Height : int := 101
    open : stream, "Maps/map" + intstr (mapNum) + ".t", get
    loop
	map_Height -= 1
	exit when map_Height = 0
	get : stream, s : *
	for i : 1 .. length (s)
	    map (i, map_Height) := ord (s (i)) - 65
	end for
    end loop
    if not eof (stream) then
	get : stream, s
	num_of_warp_points := strint (s)
	new map_Warp_points, num_of_warp_points, 5
	for i : 1 .. num_of_warp_points
	    for j : 1 .. 5
		get : stream, map_Warp_points (i, j)
	    end for
	end for
    end if
    if not eof (stream) then
	get : stream, s
	num_of_txt_objects := strint (s)
	new txt_objects, num_of_txt_objects, 4
	for i : 1 .. num_of_txt_objects
	    for j : 1 .. 4
		get : stream, txt_objects (i, j)
	    end for
	end for
    end if
    if not eof (stream) then
	get : stream, s
	num_of_interactive_objects := strint (s)
	new interactive_objects, num_of_interactive_objects, 4
	for i : 1 .. num_of_interactive_objects
	    for j : 1 .. 4
		get : stream, interactive_objects (i, j)
	    end for
	end for
    end if
    close : stream
end load_Cur_Map
var coordinates_x, coordinates_y : int := 0
var direction : int := 1
proc draw_screen (xChange : int, yChange : int)
    if not (xChange = 0 and yChange = 0) then
	direction := round ((xChange / 2 + 2.5) * abs (xChange) + ((yChange - 1) * -0.5) * abs (yChange))
	coordinates_x += xChange
	coordinates_y += yChange
	for x : -9 .. 9
	    for y : -9 .. 9
		Pic.Draw (tiles (map (coordinates_x + x, coordinates_y + y)), round ((x + 9 + xChange / 2) * 32), round ((y + 9 + yChange / 2) * 32), picCopy)
	    end for
	end for
	Pic.Draw (characters (5 + direction), (9) * 32, (9) * 32, picMerge)
	for i : 1 .. num_of_interactive_objects
	    Pic.Draw (characters (interactive_objects (i, 3) + interactive_objects (i, 4)), round ((9 + xChange / 2 + (interactive_objects (i, 1) - coordinates_x)) * 32), round ((9 + yChange / 2
		+ (interactive_objects (i, 2) - coordinates_y)) * 32), picMerge)
	end for
	View.Update
	delay (25)
    end if
    for x : -9 .. 9
	for y : -9 .. 9
	    Pic.Draw (tiles (map (coordinates_x + x, coordinates_y + y)), (x + 9) * 32, (y + 9) * 32, picCopy)
	end for
    end for
    Pic.Draw (characters (1 + direction), (9) * 32, (9) * 32, picMerge)
    for i : 1 .. num_of_interactive_objects
	Pic.Draw (characters (interactive_objects (i, 3) + interactive_objects (i, 4)), (9 + (interactive_objects (i, 1) - coordinates_x)) * 32, (9 + (interactive_objects (i, 2) - coordinates_y)) *
	    32, picMerge)
    end for
    View.Update
end draw_screen

proc print_text (text_file_num : int)
    Draw.FillBox (0, 0, maxx, 160, 0)
    Draw.Box (16, 16, maxx - 16, 144, 255)
    View.Update
    var stream : int
    var s : string
    var exitif : boolean := false
    var line : int := 1
    var line_len : int := 32
    var map_Height : int := 101
    open : stream, "Character Speech/Speech" + intstr (text_file_num) + ".t", get
    loop
	loop
	    if eof (stream) then
		exitif := true
		exit
	    end if
	    get : stream, s
	    exit when line_len + Font.Width (s + " ", font (1)) > 545
	    Font.Draw (s, line_len, 128 - line * 32, font (1), 255)
	    line_len += Font.Width (s + " ", font (1))
	    delay (50)
	    View.Update
	end loop
	exit when exitif = true
	line += 1
	line_len := 32
	Font.Draw (s, line_len, 128 - line * 32, font (1), 255)
	line_len += Font.Width (s + " ", font (1))
	delay (50)
	View.Update
	exit when eof (stream)
    end loop
    close : stream
    loop
	Input.KeyDown (chars)
	exit when chars ('x')
    end loop
end print_text

proc read_Object
    var xDir, yDir : int := 0
    case direction of
	label 0 :
	    yDir := 1
	label 1 :
	    yDir := -1
	label 2 :
	    xDir := -1
	label 3 :
	    xDir := 1
    end case
    for i : 1 .. num_of_txt_objects
	if txt_objects (i, 3) ~= 5 then
	    if coordinates_x + xDir = txt_objects (i, 1) and coordinates_y + yDir = txt_objects (i, 2) and direction = txt_objects (i, 3) then
		print_text (txt_objects (i, 4))
		exit
	    end if
	else
	    if coordinates_x + xDir = txt_objects (i, 1) and coordinates_y + yDir = txt_objects (i, 2) then
		interactive_objects (i, 4) := round ((xDir * -1 / 2 + 2.5) * abs (xDir) + ((yDir * -1 - 1) * -0.5) * abs (yDir))
		draw_screen (0, 0)
		print_text (txt_objects (i, 4))
		exit
	    end if
	end if
    end for
end read_Object



var fps := 10
var timerchk : int
load_Cur_Map (0)
View.Set ("offscreenonly")
loop
    timerchk := Time.Elapsed
    for i : 1 .. num_of_warp_points
	if coordinates_x = map_Warp_points (i, 1) and coordinates_y = map_Warp_points (i, 2) then
	    coordinates_x := map_Warp_points (i, 4)
	    coordinates_y := map_Warp_points (i, 5)
	    load_Cur_Map (map_Warp_points (i, 3))
	    exit
	end if
    end for
    Input.KeyDown (chars)
    if chars ('c') then
	read_Object
    end if
    if chars ('x') then
    end if
    if chars ('z') then
	fps := 10
    else
	fps := 5
    end if
    if chars (KEY_UP_ARROW) then
	if not (map (coordinates_x, coordinates_y + 1) ~= 1 and map (coordinates_x, coordinates_y + 1) ~= 4) then
	    if num_of_interactive_objects > 0 then
		for i : 1 .. num_of_interactive_objects
		    if not (interactive_objects (i, 1) = coordinates_x and interactive_objects (i, 2) = coordinates_y + 1) then
			draw_screen (0, 1)
			exit
		    end if
		end for
	    else
		draw_screen (0, 1)
	    end if
	end if
    elsif chars (KEY_RIGHT_ARROW) then
	if not (map (coordinates_x + 1, coordinates_y) ~= 1 and map (coordinates_x + 1, coordinates_y) ~= 4) then
	    if num_of_interactive_objects > 0 then
		for i : 1 .. num_of_interactive_objects
		    if not (interactive_objects (i, 1) = coordinates_x + 1 and interactive_objects (i, 2) = coordinates_y) then
			draw_screen (1, 0)
			exit
		    end if
		end for
	    else
		draw_screen (1, 0)
	    end if
	end if
    elsif chars (KEY_LEFT_ARROW) then
	if not (map (coordinates_x - 1, coordinates_y) ~= 1 and map (coordinates_x - 1, coordinates_y) ~= 4) then
	    if num_of_interactive_objects > 0 then
		for i : 1 .. num_of_interactive_objects
		    if not (interactive_objects (i, 1) = coordinates_x - 1 and interactive_objects (i, 2) = coordinates_y) then
			draw_screen (-1, 0)
			exit
		    end if
		end for
	    else
		draw_screen (-1, 0)
	    end if
	end if
    elsif chars (KEY_DOWN_ARROW) then
	if not (map (coordinates_x, coordinates_y - 1) ~= 1 and map (coordinates_x, coordinates_y - 1) ~= 4) then
	    if num_of_interactive_objects > 0 then
		for i : 1 .. num_of_interactive_objects
		    if not (interactive_objects (i, 1) = coordinates_x and interactive_objects (i, 2) = coordinates_y - 1) then
			draw_screen (0, -1)
			exit
		    end if
		end for
	    else
		draw_screen (0, -1)
	    end if
	end if
    end if
    draw_screen (0, 0)
    Time.DelaySinceLast (round (1000 / fps))
end loop
