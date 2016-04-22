SRCS=main.c gl_bits.c x11_bits.c

main: $(SRCS)
	gcc -Wall -o $@ $(SRCS) -lX11 -lEGL -lGLESv2 -lm -Os -flto -s
