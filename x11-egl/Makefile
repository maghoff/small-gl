SRCS=main.c gl_bits.c x11_bits.c egl_bits.c
HEADERS=vertex_glsl.h fragment_glsl.h

BASIC_FLAGS=\
	-Wall

LIBS=\
	-lX11 \
	-lEGL \
	-lGLESv2

OPTIMIZATIONS=-Os -flto -s

DEBUG_FLAGS=-ggdb

RELEASE_CFLAGS=$(LIBS) $(BASIC_FLAGS) $(OPTIMIZATIONS)
DEBUG_CFLAGS=$(LIBS) $(BASIC_FLAGS) $(DEBUG_FLAGS)

main: $(SRCS) $(HEADERS)
	gcc -o $@ $(SRCS) $(RELEASE_CFLAGS)

main-dbg: $(SRCS) $(HEADERS)
	gcc -o $@ $(SRCS) $(DEBUG_CFLAGS)

%_glsl.h: %.glsl
	xxd -i $< | sed 's/unsigned char/static const char/' > $@

.PHONY: clean
clean:
	rm -f main main-dbg *_glsl.h
