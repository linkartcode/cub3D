# cub3D
This simple project on C realises one level of the game like Return to the Castle Wolfenstein.
This demonstrates works of DDA algorithm for ray casting.
cub3D was made by Roman Protchev(@linkartcode) as the exersise for "School42" progamming school
last version 2.1 (c) 2024

For grathics out uses minilibX lib (in minilibx folder)

Type 'make' for compile to make 'cub3D' executable file.
The code is under "norminette" rules - from "School 42"'
Only five functions are in a single file and many others for better code style.

The game needs one parameter - map of level.
Mapfile must has "cub" extention. Map's is a simple text file.
Symbols for map defined in ./incl/cub3D.h file.
The map mast be closed, rectangle and has only one start position.
Examples of mapfile with errors and only one working map are in 'maps' folder

To run game type './cub3D some_map.cub' there some_map is a file of gamemap with .cub extention

Type './cub3D maps/map01.cub' to play real game
Use keys w, s, a, d to move and left/right arrows to turn to the left, right.

This is not complete game - just draft, but it works!
