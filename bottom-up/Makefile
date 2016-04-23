main: main.c Makefile
	gcc \
		-o $@ \
		-Os -s \
		-flto \
		-fno-asynchronous-unwind-tables \
		-nostartfiles \
		-nostdlib \
		$<
