main: main-prestrip
	strip -R .comment -o $@ $<

main-prestrip: main.c Makefile
	gcc \
		-o $@ \
		-Os -s \
		-flto \
		-fno-asynchronous-unwind-tables \
		-nostartfiles \
		-nostdlib \
		$<
