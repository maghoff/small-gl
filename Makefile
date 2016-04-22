main: main.c
	gcc -o $@ $< -lX11 -lEGL -lGLESv2 -lm -Os -s
