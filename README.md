microklondike
=============

microklondike is a klondike solitaire game for ANSI compatible terminals.

```console
$ mukd
-42
-
-1
#3
```

Compiling
---------

microklondike requires a C23 compiler, `make`, and POSIX compliance. To compile
microklondike, run `make`, and to run it, simply `./mukd`. For any additional
compiler flags, set `XCFLAGS` before running `make`.

Usage
-----

> **Note**    
> microklondike is a Tower of Hanoi game temporarily, while the initial code is
> still being organized. This section reflects that.

There are three towers laid horizontally across the screen, they're lines
starting with a `-`. The left is the bottom of the tower, and the right is the
top. There's also a space below showing if you have a disc on your hand, which
starts with a `#`.

If you don't have a disc on your hand, press `1`, `2`, or `3` to grab a disc
from the first, second, or third tower respectively. To put the disc down,
press one of those keys again to put down on the respective tower.

Press `q` or `Esc` to exit.

microklondike does not accept arguments.
