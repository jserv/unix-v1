# Restoration of 1st Edition UNIX from Bell Laboratories

Welcome to the 1st Edition UNIX repository. Here you will find the kernel
source code and userland binaries which will allow you to run 1e UNIX on
a PDP-11 simulator.

## Build Instructions
Unless otherwise noted, file and directory names refer to this repository.

Simply execute `make`. This will do several things.  It will build `tools/pdp11`,
`tools/mkfs`, `tools/ml` and `tools/apout/apout`. These tools are required to
build the filesystems for 1e UNIX, and the kernel. It will create kernel
sources with some necessary patches, assemble the kernel and build a bootable
[SIMH](http://simh.trailing-edge.com/) memory image which is installed into the
images directory.

Finally, the `make` will build the `rf0.dsk`, `rk0.dsk` and `tape` images and
install these in the `images` directory. You can also do a `make clean` to clean
out the `images/` and `build/` directories. A `make distclean` will clean out the
`images/`, `build/`  and `tools/` directories accordingly.

## Running 1st Edition UNIX
1. Execute `make run` or `./simh.cfg`, and you should see this:

```
PDP-11 simulator V4.0-0 Current        git commit id: fc5bda90
Disabling XQ
RF: buffering file in memory
TC0: 16b format, buffering file in memory
Listening on port 5555
```

   You will receive a `login:` prompt:

2. Type in `root` followed by RETURN key. You should receive a `#` prompt.

3. Type in an `ls -l` command. You should see something like this:

```
total    6
 43 sdrwr-  2 root    620 Jan  1 00:00:00 bin
 42 sdrwr-  2 root    250 Jan  1 00:00:00 dev
104 sdrwr-  2 root    110 Jan  1 00:00:00 etc
114 sdrwr-  2 root     50 Jan  1 00:00:00 tmp
 41 sdrwr-  7 root     70 Jan  1 00:00:00 usr
```

4. To change directories, use `chdir`, e.g. `chdir /usr`. The only editor installed
   is `ed`. You can check [A Tutorial Introduction to the UNIX Text Editor](docs/edtut.pdf) for its usage.

5. To log in multiple times, telnet to localhost port 5555.  The system
   is configured to allow 8 remote logins.

6. To shut the system down, press `Ctrl-E` to stop the simulator, and `q` to quit.
   You do not need to sync the system before shutdown.

## Documentation
The manuals for 1st Edition UNIX are available here:
<https://www.bell-labs.com/usr/dmr/www/1stEdman.html>,
<http://www.bitsavers.org/pdf/bellLabs/unix/UNIX_ProgrammersManual_Nov71.pdf>, and
<http://man.cat-v.org/unix-1st/>.

Some documentation of the internals of the 1st Edition UNIX are available here:
<http://www.bitsavers.org/pdf/bellLabs/unix/PreliminaryUnixImplementationDocument_Jun72.pdf>

Details of the PDP-11/20 architecture and its peripherals can be found at:
<http://www.bitsavers.org/pdf/dec/pdp11/handbooks/PDP1120_Handbook_1972.pdf>, and
<http://www.bitsavers.org/pdf/dec/pdp11/handbooks/PDP11_PeripheralsHbk_1972.pdf>.

The C compiler from 2nd Edition UNIX is also installed and works, but the
language is a very early dialect of C. The closest reference to the language
at this point in time is this, but it is probably 2 years too late:
<https://www.bell-labs.com/usr/dmr/www/cman74.pdf>

The userland binaries come from a period somewhere between the 1st and 2nd
Edition of UNIX. You may find the 2e manuals useful too:
<http://www.bitsavers.org/pdf/bellLabs/unix/Unix_2nd_Edition_Manual_Jun72.pdf>.

## Repository Layout
* `pages/`
    - OCR'd pages from the [Preliminary Release of UNIX Implementation Document](docs/PreliminaryUnixImplementationDocument_Jun72.pdf).
* `patches/`
    - patches to rebuilt/ files to get kernel to run
* `fs/`
    - userland binaries and files, used to make rf0.dsk and rk0.dsk
* `src/`
    - source code for userland: there is not much available
* `tools/`
    - tools and scripts to build the kernel and filesystem
* `build/`
    - build area: patched kernel files, patched filesystems
* `images/`
    - final disk and tape images to be used by the SIMH simulator
* `notes/`
    - notes on the work done to get 1e UNIX to run again

## Related Projects
* [pdp7-unix](https://github.com/DoctorWkt/pdp7-unix) resurrects Unix on the PDP-7 from scans of the original assembly code.
* [The Unix Heritage Society](https://www.tuhs.org/)
* [Unix History Repository](https://github.com/dspinellis/unix-history-repo)
* [Warner's History of Unix BSDCan 2020 Talk](https://github.com/bsdimp/bsdcan2020-demos)
* [Research UNIX v7 for Raspberry Pi](https://github.com/r1mikey/research-unix-v7)
* [ed Editor V1 Javascript Edition](https://github.com/dkkloimwieder/eded.js)
* [pdp11-B](https://github.com/rswier/pdp11-B)  is an effort to recreate the B compiler for the PDP-11 as authentically as possible.
