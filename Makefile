SRCS=main.c gl_bits.c x11_bits.c egl_bits.c

main: $(SRCS) vertex_glsl.h fragment_glsl.h
	gcc \
		-Wall \
		-o $@ $(SRCS) \
		-lX11 \
		-lEGL \
		-lGLESv2 \
		-lm \
		-Os -flto -s

%_glsl.h: %.glsl
	xxd -i $< | sed 's/unsigned char/static const char/' | sed 's/unsigned int.*//' > $@

.PHONY: clean
clean:
	rm -f main *_glsl.h
