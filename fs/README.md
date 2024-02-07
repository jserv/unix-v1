# filesystem

The directories `root` and `usr` contain the files from the "s2-bits tape",
which Dennis Ritchie extracted from an old DECtape at Bell Labs, which is
available here: <https://minnie.tuhs.org/TUHS/Archive/Distributions/Research/1972_stuff/>

Dennis notes that "s2-bits is not source, but a dump of (parts of) `/bin`,
`/etc`, `/usr/lib`, and bits of a few other directories".

## Layout
The files on the "s2-bits tape" are split into two directories:
* `root` - files from `s2.tar.gz`, excluding the usr directory, used to populate
  the rf0 filesystem.
* `usr` - files from `s2.tar.gz` under the usr directory, used to populate the
  rk0 filesystem.

Binaries which have been built recently while reconstructing the system
are in the `new` directory, and include:

`new/etc/init` - built from jun72 printout sources for `init.s` with
modifications to spawn getty on tty8 (console) only.

## File Permissions
The following list gives details of all the files in the s2-bits tap-format
archive. The first columns are a direct copy of a listing done with the
emulated 1st Edition tap(1) from the s2-bits tape.

The last column gives the file's modified timestamp (in decimal)
as recorded in the archive: I captured the smdate(2) argument in Apout
as tap(1) tried to extract the archive. This is in 1/60th second units.

The list is sorted by the TAP DATE column.
```
MODE  UID SIZE  TAPA    DATE     NAME                 TAP DATE
===============================================================
-rwr-  0 16448  538 Jan  1 00:33 /core                  121912 
-rwr- 10    54  529 Jan  1 00:52 /usr/x                 188944 
-rwr- 10    84  474 Jan  1 00:58 /usr/jack/x.f          209544 
-rwr-  0   312  490 Jan  1 00:58 /usr/jack/x.o          210381 
xrwr-  0  7514  475 Jan  1 00:58 /usr/jack/a.out        210836 
-r-r-  1  1664  533 Jan  1 01:31 /tmp/etma              328795 
-rwr-  1   670  530 Jan  1 01:33 /usr/ken/maki.s        336810 
-rwr-  0   142  532 Jan  1 01:33 /tmp/utmp              337991 
-rwr-  0   512  259 Jan  1 01:33 /etc/std0              338378 
xrwr-  0   698  229 Jan  1 01:35 /bin/maki              344095 
-rwr-  0    26  537 Jan  1 01:35 /tmp/ttmp              344821 
-rwr-  0 16448  260 Jan  1 01:36 /usr/sys/core          347684 
-rwr-  1  1928  298 Jan  1 01:36 /usr/sys/maki.s        348923 
xrwr-  0  2192  293 Jan  1 01:37 /usr/sys/a.out         349375 
xrwr-  3  1912  135 Jan  4 17:05 /bin/form              19243860 
urwr-  0  3940  142 Jan  5 19:26 /bin/mail              24936840 
xrwr-  1  2662  241 Jan  6 18:01 /etc/glob              29812654 
xrwr-  1   186  240 Jan  6 18:01 /etc/msh               29812724 
urwr-  0   784   50 Jan 17 17:46 /bin/mv                86785042 
xrwr-  3   134  114 Jan 17 17:53 /bin/cat               86808907 
xrwr-  3    82   25 Jan 17 17:53 /bin/chmod             86808926 
xrwr-  3   420   93 Jan 17 17:53 /bin/cmp               86808947 
xrwr-  3   160   48 Jan 17 17:53 /bin/cp                86808966 
xrwr-  3   464   79 Jan 17 17:53 /bin/du                86809052 
xrwr-  3   104   49 Jan 17 17:53 /bin/ln                86809162 
xrwr-  3  2010   42 Jan 17 17:53 /bin/ls                86809182 
xrwr-  3   154  126 Jan 17 17:53 /bin/mesg              86809205 
xrwr-  3    70  121 Jan 17 17:53 /bin/rew               86809297 
xrwr-  3    93   52 Jan 17 17:53 /bin/rm                86809316 
xrwr-  3  1026   54 Jan 17 17:53 /bin/stat              86809356 
xrwr-  3    80  125 Jan 17 17:53 /bin/tty               86809419 
xrwr-  3   524   57 Jan 17 17:53 /bin/write             86809532 
xrwr-  3   560   77 Jan 17 17:54 /bin/who               86813788 
xrwr-  3   644  139 Jan 17 17:54 /bin/wc                86813793 
xrwr-  3   750  164 Jan 17 17:54 /bin/skip              86813802 
xrwr-  3  1166  115 Jan 17 17:54 /bin/pr                86813803 
xrwr-  3   300  141 Jan 17 17:54 /bin/od                86813807 
xrwr-  3  1844  159 Jan 17 17:56 /bin/if                86819396 
xrwr-  3  1154  156 Jan 17 17:56 /bin/goto              86819398 
xrwr-  3   276  163 Jan 17 17:56 /bin/exit              86819403 
xrwr-  3  1054  153 Jan 17 17:56 /bin/echo              86819406 
xrwr-  3   244   60 Jan 17 17:56 /bin/dsw               86819407 
xrwr-  3  5922   80 Jan 17 17:56 /bin/bas               86819408 
xrwr-  3    16  152 Jan 17 17:56 /bin/:                 86819410 
xrwr-  1   954   32 Jan 19 17:20 /bin/sh                97059255 
xrwr-  3  2310  103 Jan 26 17:20 /bin/ar                133346922 
xrwr-  3  1048  166 Jan 31 18:14 /bin/stty              159458885 
xrwr-  6  2860  169 Mar  7 12:23 /bin/cal               339637168 
-rwr-  3  2082  233 Mar 28 16:42 /etc/suftab            449432781 
urwr-  0  1290   28 Mar 29 15:19 /bin/login             454317684 
xrwr-  3  4066   95 Mar 29 16:42 /bin/db                454616955 
xrwr-  3    76   94 Apr  6 19:42 /bin/chball            496735250 
xrwr-  3   446  232 Apr  7 16:40 /etc/getty             501264829 
xrwr-  3  6846  176 Apr 14 20:50 /bin/dc                538454712 
urwr-  0   794   26 Apr 20 23:45 /bin/date              570186721 
urwr-  0   746  190 May  3 22:54 /bin/su                637395674 
xrwr-  3  3998  127 May 10 15:23 /bin/ed                672059949 
xrwr-  3   330  213 May 27 00:21 /bin/find              756940137 
xrwr-  3   480   59 May 27 00:21 /bin/strip             756940428 
urwr-  1   872  211 May 27 00:26 /bin/ds                756957948 
xrwr- 10  2730  192 May 27 23:37 /bin/fc                761966733 
xrwr-  3 17092  346 Jun  6 21:26 /usr/lib/c1            813333853 
-rwr-  0  3498  339 Jun  9 17:10 /usr/lib/bilib.a       827964344 
-rwr-  0  6626  326 Jun 20 10:47 /usr/lib/libb.a        883611316 
xrwr-  3  7582  214 Jun 30 17:45 /bin/as                936955268 
xrwr-  3  5778  247 Jun 30 17:47 /etc/as2               936962166 
xrwr-  3   238  118 Jun 30 18:37 /bin/un                937143109 
-rwr-  0 12158  302 Jun 30 18:40 /usr/lib/liba.a        937154143 
xrwr-  3  2942  108 Jun 30 19:26 /bin/ld                937319472 
xrwr-  3   518   75 Jun 30 20:09 /bin/nm                937472871 
xrwr-  3  1446  208 Jun 30 20:15 /bin/size              937496145 
-rwr-  6   304  448 Jun 30 20:31 /usr/lib/fr0.o         937553564 
-rwr-  6 12222  449 Jun 30 20:37 /usr/lib/filib.a       937573356 
-rwr-  6  9158  419 Jun 30 20:46 /usr/lib/libf.a        937606048 
-rwr-  0   108  473 Jun 30 21:11 /usr/lib/crt0.o        937696858 
-rwr-  0  5242  437 Jun 30 21:20 /usr/lib/libc.a        937728015 
xrwr-  3 19948  380 Jun 30 21:21 /usr/lib/c0            937734428 
xrwr-  3  4672  198 Jun 30 21:53 /bin/cc                937848855 
xrwr-  6  3462  491 Jul  1 16:35 /usr/fort/fc1          941888104 
xrwr-  6  3238  498 Jul  1 16:35 /usr/fort/fc2          941888184 
xrwr-  6  6840  505 Jul  1 16:35 /usr/fort/fc3          941888472 
xrwr-  6  4918  519 Jul  1 16:35 /usr/fort/fc4          941888613 
xrwr-  3   214  175 Jul 15 01:21 /bin/sum               1011175062 
xrwr-  4  7154   61 Jul 21 12:42 /bin/roff              1044729738 
urwr-  0   282   53 Sep 28 21:37 /bin/rmdir             1404349922 
urwr-  0   232   31 Nov  6 21:42 /bin/mkdir             1606544287 
urwr-  1   192   92 Nov 22 19:35 /bin/df                1689030995 
urwr-  1  1084  122 Nov 22 19:35 /bin/check             1689030997 
xrwr-  3   718   46 Nov 22 22:51 /bin/chown             1689737545 
xrwr-  3   604  150 Nov 22 22:51 /bin/sort              1689737557 
urwr-  1   790  119 Nov 26 14:24 /bin/tm                1708647263 
urwr-  0  3678   34 Dec 31 04:08 /bin/tap               1887871165 
-rw--  1   221  239 Feb  6 14:35 /etc/passwd            2081934621 
-rwr-  1    70  238 Feb  6 14:38 /etc/uids              2081948231 
xrwr-  1   424  231 Feb  6 14:50 /etc/init              2081988977 
```
