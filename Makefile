main: main.c
	gcc -Wall -o $@ $< -lX11 -lEGL -lGLESv2 -lm -Os -s
