# Sprite Cutter

Sprite Cutter is a binary made to help primarily game creators to cut sprite sheet into a certain amount of sprites.
It is meant to be very simple to use.

## How to use

Use `make install` in the current directory.

Then, use the binary as follows :

`./sprite_cutter [Source sheet] [Sprite size]`

 * The source sheet is the sprite sheet to cut from. (jpg or png).

 * The Sprite size is the wanted size of the sprites in the end. (in pixels, and usually a power of 2 like 32, 64 or 128).

Sprite Cutter will then cut the source sheets in image of **sprite_size\*sprite_size** pixels, in the form of **png files**.

Their names will be composed with two numbers, like **1-0.png**. The first number is the index of the row the sprite was at, and the second its column.

The files will be created in the same directory you called sprite_cutter.

## Credits

Kaïs-Khan Hadi, Engineering Student at the ENSEIRB-MATMECA.
This software is free to use, you don't have to ask.
