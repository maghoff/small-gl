main: main.cpp
	g++ -o $@ $< -lX11 -lEGL -lGLESv2 -Os -s -nostartfiles
