# Apout -- Simulate PDP-11 Unix a.out binaries

## Introduction
This program is a user-level simulator for UNIX a.out binaries. Binaries
for V1, V2, V5, V6, V7, 2.9BSD and 2.11BSD can be run with this simulator.
The user-mode PDP-11 instructions are simulated, and TRAP instructions
are emulated by calling equivalent native-mode system calls.

The advantages of an a.out simulator over a full-blown PDP-11 simulator are:
+ system calls can be done natively, thus speeding up execution
+ the simulator is less of a CPU-hog than a full-blown PDP-11 simulator
+ you don't need a simulated operating system or a simulated file system

## Status
The program is now at release 2.3 Alpha2. Most of the binaries from V5, V6
and V7 run fine. All of the V5/V6/V7 system calls are caught, but some are
ignored and some generate EPERM errors. The V1, V2, 2.9BSD and 2.11BSD
environments are still under construction: see the file `LIMITATIONS` for
details. Finally, the simulator won't run on a big-endian machine.

## Installation
I have only tested this program on FreeBSD 2.x and 3.x, and on RedHat
Linux 2.2. It should compile on a 32-bit little-endian machine with
some form of Unix; you may need to change some header file includes etc.
See `defines.h' for the details.

If you remove the `-DEMU211` macro definition from the `Makefile`, the emulation
of 2.11BSD will not be compiled in to the simulator. Similarly, if you remove
the `-DEMUV1` macro definition from the Makefile, the emulation of 1st and 2nd
Edition UNIX will not be compiled in to the simulator. By default, EMUV1
is disabled.

Once you have configured apout, now type `make'. Hopefully, things will
compile ok. You will eventually get the `apout' program.

Now go find an old PDP-11 UNIX binary, e.g 7th Edition cal, and say:
```shell
$ setenv APOUT_ROOT /		# for now
$ apout cal 1970
```

If the simulator is working, the calendar for 1970 will be printed out.
The V7 shell works, and from there, you can run other programs.
```shell
$ apout sh
# ls -l
  (output of ls)
```

Finally, install apout in /usr/local/bin, and the manual page apout.1 in
the appropriate place. If you can't use the man page because of incompatible
macros, then apout.0 is a text file which has the pre-formatted man page.

## Environment Variables
Apout has the concept of a simulated root filesystem for the simulated PDP-11
binaries. When working with filenames, if the filenames are relative, they
stay relative. If the filenames are absolute (i.e `/usr/...`), then apout
prepends the value of the environment variable `APOUT_ROOT` to the filename.
This allows you to say:
```shell
# setenv APOUT_ROOT /usr/misc/v7root
```
before running apout to set the `root' of the filesystem wherever you want.
You MUST set APOUT_ROOT before running apout.

## TODO
There's lots to do. Here's what I'd like to do, in a somewhat ordered list.

	+ Verify that the instruction simulation and	high priority
	     the syscalls all work correctly
	+ Complete some of the syscalls that are	med priority
	     not fully simulated
	+ Speed the simulator up 			med priority

## Source Organization
`main.c`		parses any arguments, loads the binary and calls run()
`cpu.c`		holds the main instruction decode/execute loop
`itab.c`		holds function lookup tables for all instructions
`ea.c`		holds functions to decode the PDP-11 addressing modes

`single.c`	single.c, double.c and branch.c hold most of the functions
`double.c`	 which perform the PDP-11 user-mode instructions. The code
`branch.c`	 in these files comes from a PDP-11 simulator by Eric Edwards
`fp.c`		partially emulates FP instructions

`aout.c`		determines what type of a.out the binary is, and what UNIX
`magic.c`		 environment to set up. If V5/V6/V7, trap instructions fall
`v7trap.c`	 into v7trap.c which runs them using native system calls
`v7trap.h`

`v1trap.c`	if the binary is a 1st or 2nd Edition binary, traps fall
`v1trap.h`	 into v1trap.c, which likewise does the syscalls natively
`ke11a.c`		emulates the KE11A extended arithmetic unit, used by V1/V2

`bsdtrap.c`	if the binary is a 2.11BSD binary, trap instructions fall
`bsdtrap.h`	 into bsdtrap.c, which likewise does the syscalls natively
`bsd_ioctl.c`	2.11BSD ioctl calls are handled with this file

`defines.h`	holds function & typedef prototypes and useful cpp macros
