# Early C compiler

This directory contains the last1120c C compiler, as described by Dennis Ritchie
on his web page: <https://www.bell-labs.com/usr/dmr/www/primevalC.html>.

You can use the Apout emulator and the C compiler from the s2 tape to recompile
the last1120c compiler. After installing the new compiler binaries, last1120c
can recompile itself.

Here are the instructions:
1. First, compile and install the Apout emulator. Ensure that you have enabled
   `-DEMUV1` in the Makefile.
2. Unpack the V1 executables from the s2 tape into a suitable area, e.g.,
   `/usr/local/src/V1`. Set the environment variable `APOUT_ROOT` to this
   directory.
3. Change to the `last1120c` directory and edit the shell script mak so that it
   reflects the `APOUT_ROOT` value you have chosen. Then, simply run the mak
   shell script natively. This process will build the front-end command, cc,
   and the two passes of the C compiler: c0 and c1.
4. If desired, you can now move c0 and c1 into `$APOUT_ROOT/usr/lib`, replacing
   the original c0 and c1. Then use the shell script mak again to rebuild c0 and
   c1 using themselves. Similarly, you can replace `$APOUT_ROOT/bin/cc` with the
   cc created here.

The C compiler can now mostly rebuild itself on the V1 kernel, except for the
c1 pass, which does not work yet. The `v1mak` shell script can be run on V1 to
rebuild everything from source.
