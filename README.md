# Restoration of 1st Edition UNIX from Bell Laboratories

Welcome to the 1st Edition UNIX repository. Here, you will find the kernel
source code and userland binaries necessary to run 1st Edition UNIX on a
PDP-11 simulator. This repository houses a reconstructed version of UNIX as
it existed around 1972, rather than an original 1st Edition UNIX image.
The reconstruction is based on a printout of the UNIX kernel slightly after
Version 1, supplemented with data recovered from a DECtape dating from around
Versions 2 or 3.

The 1st Edition UNIX marked a significant milestone when UNIX was rewritten
for the then-new PDP-11, a relatively affordable minicomputer, transitioning
from the PDP-7 for which it was originally developed, at Bell Laboratories.
Both versions were crafted in assembly language. The early iterations of UNIX
were quintessential examples of advanced concepts encapsulated within
streamlined systems. The influence of UNIX has been so profound that its
impact resonates well into the 21st century. The developmental history of UNIX
is well-documented, and in the past decade, concerted efforts have been made
to locate and preserve software and documentation artifacts from UNIX's
formative years.

The paper titled "[The Restoration of Early UNIX Artifacts](https://www.usenix.org/legacy/event/usenix09/tech/full_papers/toomey/toomey.pdf)"
by Warren Toomey provides an in-depth account of the endeavors to restore
these historical artifacts to operational condition, along with the valuable
insights gained through this process.

## Build Instructions
Unless otherwise noted, file and directory names refer to this repository.

Simply execute `make`. Doing so initiates several processes. It compiles
`tools/pdp11`, `tools/mkfs`, `tools/ml`, and `tools/apout/apout`. These tools
are essential for constructing the filesystems and the kernel for 1st Edition
UNIX. Additionally, the command prepares kernel sources with requisite patches,
assembles the kernel, and creates a bootable [SIMH](http://simh.trailing-edge.com/)
memory image. This image is then placed into the images directory.

Finally, the `make` will build the `rf0.dsk`, `rk0.dsk` and `tape` images and
install these in the `images` directory. You can also do a `make clean` to clean
out the `images` and `build` directories. A `make distclean` will clean out the
`images`, `build`  and `tools` directories accordingly.

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
<https://www.tuhs.org/Archive/Distributions/Research/Dennis_v1/UNIX_ProgrammersManual_Nov71.pdf>, and
<https://man.cat-v.org/unix-1st/>.

Some documentation of the internals of the 1st Edition UNIX are available here:
<http://www.bitsavers.org/pdf/att/unix/Early_UNIX/PreliminaryUnixImplementationDocument_Jun72.pdf>

Details of the PDP-11/20 architecture and its peripherals can be found at:
<http://www.bitsavers.org/pdf/dec/pdp11/handbooks/PDP1120_Handbook_1972.pdf>, and
<http://www.bitsavers.org/pdf/dec/pdp11/handbooks/PDP11_PeripheralsHbk_1972.pdf>.

The C compiler from 2nd Edition UNIX has been installed and is operational.
However, it supports a very early dialect of C. The most relevant reference for
this version of the language is as follows, although it may be approximately
two years more advanced than the dialect in question:
<https://www.bell-labs.com/usr/dmr/www/cman74.pdf>

The userland binaries originate from a period between the 1st and 2nd Editions
of UNIX. The manuals from the 2nd Edition may also be useful:
<http://www.bitsavers.org/pdf/att/unix/Early_UNIX/Unix_2nd_Edition_Manual_Jun72.pdf>.

## Repository Layout
* `pages`
    - OCR'd pages from the [Preliminary Release of UNIX Implementation Document](docs/PreliminaryUnixImplementationDocument_Jun72.pdf).
* `patches`
    - patches to rebuilt files to get kernel to run
* `fs`
    - userland binaries and files, used to make rf0.dsk and rk0.dsk
* `src`
    - source code for userland: there is not much available
* `tools`
    - tools and scripts to build the kernel and filesystem
* `build`
    - build area: patched kernel files, patched filesystems
* `images`
    - final disk and tape images to be used by the SIMH simulator
* `notes`
    - notes on the work done to get 1e UNIX to run again

## License

In 2002, Caldera International made Unix V1 through V7 for PDP-11 and Unix 32V
for VAX available as free and open source software, adopting a permissive
BSD-style license. Consequently, any work derived from Unix V1, as well as
portions of V2 and V3, falls under this same BSD-style licensing.

Use of this repository is governed by a BSD-style license that can be found in
the [LICENSE](LICENSE) file. Apout is redistributed under the MIT License,
which can be found in the [LICENSE.Apout](LICENSE.Apout) file.

Check the [CREDITS](CREDITS) file to see who participated in the restoration.

## Related Projects
* [7th Edition Unix at 40](https://2019.eurobsdcon.org/slides/7th%20Edition%20Unix%20at%2040%20-%20Warner%20Losh.pdf) / [video](https://youtu.be/FTlzaDgzPY8)
* [pdp7-unix](https://github.com/DoctorWkt/pdp7-unix) resurrects Unix on the PDP-7 from scans of the original assembly code.
* [The Unix Heritage Society](https://www.tuhs.org/)
* [Unix History Repository](https://github.com/dspinellis/unix-history-repo)
* [Warner's History of Unix BSDCan 2020 Talk](https://github.com/bsdimp/bsdcan2020-demos)
* [Research UNIX v7 for Raspberry Pi](https://github.com/r1mikey/research-unix-v7)
* [ed Editor V1 Javascript Edition](https://github.com/dkkloimwieder/eded.js)
* [pdp11-B](https://github.com/rswier/pdp11-B)  is an effort to recreate the B compiler for the PDP-11 as authentically as possible.
* [B compiler](https://github.com/aap/b) is capable of compiling itself.
