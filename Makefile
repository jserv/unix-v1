all:
	$(MAKE) -C tools
	$(MAKE) -C build install

run: all
	tools/pdp11 simh.cfg

clean:
	$(MAKE) -C build clean

distclean: clean
	$(MAKE) -C tools clean
	$(MAKE) -C build distclean
