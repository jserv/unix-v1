# Makefile for Apout PDP-11 application emulator
#
# You will need gcc if you choose the optimised compile below
CC ?= gcc

# If you don't want 2.11BSD emulation, then remove the -DEMU211 flag.
# Set up the LIBS if required for your system
#
# These flags should be fine for most cases
APOUT_OPTIONS ?= -DEMU211 -DEMUV1 -DNATIVES

# Assemble CFLAGS
CFLAGS ?= -O2 -finline-functions -fomit-frame-pointer
CFLAGS +=-Winline -Wunused-result # silence warnings
CFLAGS += $(APOUT_OPTIONS)

# Any extra libraries required
LIBS= -lm

# Install destinations
PREFIX ?=/usr/local
MANDIR = $(PREFIX)/man/man1
BINDIR = $(PREFIX)/bin

VERSION = apout2.3beta1
SRCS = \
	cpu.c aout.c aout.h branch.c double.c ea.c itab.c main.c ke11a.c \
	single.c fp.c v7trap.c bsdtrap.c defines.h v7trap.h \
	bsdtrap.h bsd_ioctl.c bsd_signal.c magic.c v1trap.c v1trap.h
OBJS = \
	aout.o branch.o bsd_ioctl.o bsd_signal.o bsdtrap.o cpu.o \
	double.o ea.o fp.o itab.o ke11a.o magic.o main.o single.o v1trap.o \
	v7trap.o

apout: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o apout $(LIBS)

install: apout apout.1
	cp apout $(BINDIR)
	chmod 755 $(BINDIR)/apout
	cp apout.1 $(MANDIR)
	chmod 644 $(MANDIR)/apout.1

clean:
	rm -rf apout *core $(OBJS) *.dbg $(VERSION) $(VERSION).tar.gz apout.0

apout.0: apout.1
	nroff -man apout.1 > apout.0

indent: $(SRCS)
	astyle --style=kr $(SRCS)

disttar: clean apout.0
	- mkdir $(VERSION)
	cp $(SRCS) $(VERSION)
	chmod -R go+rX $(VERSION)
	chmod -R u+w $(VERSION)
	chown -R wkt $(VERSION)
	tar vzcf $(VERSION).tar.gz $(VERSION)

# Dependencies for object files
aout.o: aout.c defines.h aout.h Makefile
branch.o: branch.c defines.h Makefile
bsd_ioctl.o: bsd_ioctl.c defines.h Makefile
bsd_signal.o: bsd_signal.c defines.h bsdtrap.h Makefile
bsdtrap.o: bsdtrap.c bsdtrap.h defines.h Makefile
cpu.o: cpu.c defines.h Makefile
double.o: double.c defines.h Makefile
ea.o: ea.c defines.h Makefile
fp.o: fp.c defines.h Makefile
itab.o: itab.c defines.h Makefile
ke11a.o: ke11a.c defines.h Makefile
magic.o: magic.c defines.h Makefile
main.o: main.c defines.h Makefile
single.o: single.c defines.h Makefile
v1trap.o: v1trap.c v1trap.h defines.h Makefile
v7trap.o: v7trap.c v7trap.h defines.h Makefile
