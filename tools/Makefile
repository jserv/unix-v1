CFLAGS=-g -Wall

all: pdp11 mkfs ml apout/apout

pdp11: simh/makefile
	$(MAKE) -C simh NOVIDEO=1 pdp11
	ln -sf simh/BIN/pdp11 .

simh/makefile:
	git submodule update --init

mkfs: mkfs.c

ml: ml.c

apout/apout:
	($(MAKE) -C apout; rm -f apout/*.o)

clean:
	rm -f pdp11
	$(MAKE) -C simh clean
	rm -f mkfs ml
	$(MAKE) -C apout clean
