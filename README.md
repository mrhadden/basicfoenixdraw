# basicfoenixdraw
Basic Drawing in C on the C256 Foenix


To build open a command line and switch to the cloned directory.

Run cmake.bat

This should build the BIN/HEX

With output like this:
***
G:\devprojects\6502\GitBasicDraw>cmake
Could Not Find G:\devprojects\6502\GitBasicDraw\basic.s
WDC 65816 C   Version 3.49  Jan 19 2006 14:38:08
      Copyright (C) 1992-2006 by The Western Design Center, Inc.
WDC 65C816 Assembler  Version 3.49.1 Feb  6 2006 17:24:51
       Copyright (C) 1992-2006 by The Western Design Center, Inc.
allocated 4364 bytes of memory.
WDC 65C816 Linker Version 3.49.1 Apr 24 2006 15:40:38
   Copyright (C) 1992-2006 The Western Design Center, Inc.

Section: ORG:    ROM ORG:  SIZE:
CODE     1A0000  1A0000      C51H (  3153)
DATA     190000  190000        CH (    12)
startup  18C000  18C000        EH (    14)
startupx 00C000  00C000        EH (    14)
reset    18FFFC  18FFFC        2H (     2)
resetx   00FFFC  00FFFC        2H (     2)
Total                        C7DH (  3197)

WDC 65C816 Linker Version 3.49.1 Apr 24 2006 15:40:38
   Copyright (C) 1992-2006 The Western Design Center, Inc.

Section: ORG:    ROM ORG:  SIZE:
CODE     1A0000  1A0000      C51H (  3153)
DATA     190000  190000        CH (    12)
startup  18C000  18C000        EH (    14)
startupx 00C000  00C000        EH (    14)
reset    18FFFC  18FFFC        2H (     2)
resetx   00FFFC  00FFFC        2H (     2)
Total                        C7DH (  3197)

srec_cat.exe: myprog.s28.hex: 1: warning: no header record
myprog.hex
myprog.s28.hex
        2 file(s) copied.
myprog.bin
***
