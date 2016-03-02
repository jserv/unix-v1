CFLAGS=-g -Wall

all: mkfs ml apout/apout

mkfs: mkfs.c

ml: ml.c

apout/apout:
	($(MAKE) -C apout; rm -f apout/*.o)

clean:
	rm -f mkfs ml
	$(MAKE) -C apout clean
