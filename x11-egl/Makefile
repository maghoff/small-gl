SRCS=main.c gl_bits.c x11_bits.c egl_bits.c
HEADERS=vertex_glsl.h fragment_glsl.h

BASIC_FLAGS=\
	-Wall

LIBS=\
	-lX11 \
	-lEGL \
	-lGLESv2

OPTIMIZATIONS=\
	-Os -flto -s \
	-fno-asynchronous-unwind-tables

DEBUG_FLAGS=-ggdb

RELEASE_CFLAGS=$(BASIC_FLAGS) $(OPTIMIZATIONS)
DEBUG_CFLAGS=$(BASIC_FLAGS) $(DEBUG_FLAGS)

main: main.xz
	echo 'dd bs=1 skip=60<$$0|xz -d>/tmp/C;chmod +x /tmp/C;/tmp/C;exit' > $@
	cat $< >> $@
	chmod a+x $@

main.xz: main-bin
	xz -c9e $< > $@

main-bin: main-prestrip
	strip \
		-R .comment \
		-R '.note*' \
		-R '.eh*' \
		-o $@ \
		$<

main-prestrip: $(SRCS) $(HEADERS)
	gcc -o $@ $(RELEASE_CFLAGS) $(SRCS) $(LIBS)

main-dbg: $(SRCS) $(HEADERS)
	gcc -o $@ $(DEBUG_CFLAGS) $(SRCS) $(LIBS)

%_glsl.h: %.glsl
	xxd -i $< | sed 's/unsigned char/static const char/' > $@

.PHONY: clean
clean:
	rm -f main main-dbg *_glsl.h
