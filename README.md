# Motorola 68xx Assemblers

This repository contains the source code to build cross
assemblers for the Motorola 6800 family of 8bit processors.  This code was
originally published in 1984 and then ported to the IBM PC and republished
in 1987.  The original code is in Jim Newman's
[motorola-6800-assembler repository](https://github.com/JimInCA/motorola-6800-assembler)
on github.

The original code suffers from some limitations:
- No attempt is made to validate the use of CPU variant specific instructions
- Output files are always created alongside the input files
- Some fixed length assumptions are made for file arguments

To address these shortcomings, the code has been migrated to C++ and some
small enhancements made.  Jim Newman's intent was to keep the source code
as close to the original as possible.  However, since enhancements are no
longer being made to the original source code, deviating from that code
should not be a problem.

## Building

The code uses [CMake](https://cmake.org) and has no external dependencies,
so building the code is a simple matter of configuring with CMake and then
using your generated build scripts, e.g. with make:
```
mkdir build
cd build
cmake ..
make
```

This results in an assembler for each processor variant:

| Program | Processor |
| ------- | --------- |
| `as0`   | 6800/6802 |
| `as1`   | 6801      |
| `as4`   | 6804      |
| `as5`   | 6805      |
| `as9`   | 6809      |
| `as11`  | 68HC11    |


## Documentation

Included in the `documentation` directory are two files.  File
`assembler.txt` is the original documentation included with the sources for
the assemblers.  The other file, `motorola_cross_asm_manual.pdf` is a manual
for the Motorola assemblers that was published in 1990.  The information in
this second file is not absolutely consistent with the assemblers used here,
but it seems to be close and is a much more complete document than the text
file.  So use at your own discretion.

## Enhancements

The original assemblers have been enhanced with a `cpu` pseudo opcode.  This
opcode takes a single argument that specifies the variant of the CPU in order
to validate that CPU-specific opcodes are only used where intended.  The
value of the argument can be:

| Argument | Meaning |
| -------- | ------- |
| `cmos`   | CMOS 6805 supporting `STOP` and `WAIT` instructions |
| `hc05c4` | HC05C4 6805 supporting `MUL` instruction |

## Testing Your Binary

The `test` directory contains some sample assembly language programs.
The files `all_6805_opcodes_by_name.asm` and `all_6805_opcodes_by_value.asm`
exercise every 6805 mnemonic and can be usd to validate all 6805 opcodes.

The `help.asm` and `used5.asm` programs are examples from the
[MEK6802D5 Microcomputer Evaluation Board User's Manual](https://github.com/JimInCA/cassette-tape-emulator/blob/main/doc/mek6802d5.pdf).
The code is almost identical to the code in the book with the exception of
the opt pre-assembler directive and the addition of a few comments of mine.

These programs can be used to verify
the functionality of the assembler binaries.  A simple procedure follows that
you can use to test the assemblers:
```
as0 used5.asm -l cre c s
```
Using the above command, the output to the terminal window from the as0
assembler should look like this:
```
$ as0 used5.asm -l cre c s
0001                               *
0002                               *        Copied from:
0003                               *        MEK6802D5 Microcomputer Evaluation Board User's Manual
0004                               *        Page 3-8
0005                               *
0006                               *        Assemble with the following command:
0007                               *            as0 used5.asm -l cre c s
0008                               *
0009                                       nam     used5
0010                               *       Options set in file override command line option settings
0011                               *        opt     c       * options must be in lower case
0012 0000                                  org     $0
0013 e41d                          disbuf  equ     $e41d
0014 f0a2                          diddle  equ     $f0a2
0015 e419                          mnptr   equ     $e419
0016 f0bb                          put     equ     $f0bb
0017                               *
0018 0000 86 3e              [ 2 ] beg     ldaa    #$3e     "U"
0019 0002 b7 e4 1d           [ 5 ]         staa    disbuf   store to first display
0020 0005 86 6d              [ 2 ]         ldaa    #$6d     "S"
0021 0007 b7 e4 1e           [ 5 ]         staa    disbuf+1
0022 000a 86 79              [ 2 ]         ldaa    #$79     "E"
0023 000c b7 e4 1f           [ 5 ]         staa    disbuf+2
0024 000f 86 00              [ 2 ]         ldaa    #$00     blank
0025 0011 b7 e4 20           [ 5 ]         staa    disbuf+3
0026 0014 86 5e              [ 2 ]         ldaa    #$5e     "D"
0027 0016 b7 e4 21           [ 5 ]         staa    disbuf+4
0028 0019 86 6d              [ 2 ]         ldaa    #$6d     "5"
0029 001b b7 e4 22           [ 5 ]         staa    disbuf+5 store to last display
0030 001e ce f0 a2           [ 3 ]         ldx     #diddle  adder of diddle routine
0031 0021 ff e4 19           [ 6 ]         stx     mnptr    establish as active sub of "PUT"
0032 0024 7e f0 bb           [ 3 ]         jmp     put      call display routine
0033                                       end

beg        0000
diddle     f0a2
disbuf     e41d
mnptr      e419
put        f0bb

beg        0000 *0018
diddle     f0a2 *0014 0030
disbuf     e41d *0013 0019 0021 0023 0025 0027 0029
mnptr      e419 *0015 0031
put        f0bb *0016 0032 
```

The as0 assembler produces the S-recored output file `used5.s19`.  This file is
saved to the `test` directory.  A listing of the test directory should look
like this:

```
$ ls -al
total 20
drwxrwxr-x 2 jim jim 4096 May 29 07:53 .
drwxrwxr-x 8 jim jim 4096 May 29 07:53 ..
-rw-rw-r-- 1 jim jim  657 May 26 18:56 help.asm
-rw-rw-r-- 1 jim jim  778 May 26 18:56 used5.asm
-rw-rw-r-- 1 jim jim  109 May 29 07:53 used5.s19
```

The first example, `used5.asm`, was written using only lower case characters
and no tabs.  As a further test of the assembler, test case `help.asm` was
written using only upper case characters along with tabs to set the spacing
between the label, operator, operand, and comment fields.  You can assemble
`help.asm` with the following command:

```
as0 help.asm -L CRE C S
```

This will produce the following output to the terminal window along with the
`help.s19` file being written to the `test` directory:

```
$ as0 help.asm -L CRE C S
0001                               *
0002                               *	Copied from:
0003                               *	MEK6802D5 Microcomputer Evaluation Board User's Manual
0004                               *	Page 3-10
0005                               *
0006                               *	Assemble with the following command:
0007                               * 	as0 help.asm -L CRE C S
0008                               *
0009                               	NAM	HELP
0010                               *	Options set in file override command line option settings.
0011                               *	OPT	c		* options must be in lower case
0012                               *	OPT	cre		* one option per line
0013 0000                          	ORG	$0
0014                               * D5 DEBUT ROUTINES
0015 f0a2                          DIDDLE	EQU	$F0A2
0016 e41d                          DISBUF	EQU	$E41D
0017 e419                          MNPTR	EQU	$E419
0018 f0bb                          PUT	EQU	$F0BB
0019                               *
0020                               *
0021 0000 ce 76 79           [ 3 ] BEG	LDX	#$7679		"HE"
0022 0003 ff e4 1d           [ 6 ] 	STX	DISBUF		STORE TO FIRST 2 DISPLAYS
0023 0006 ce 38 73           [ 3 ] 	LDX	#$3873		"LP"
0024 0009 ff e4 1f           [ 6 ] 	STX	DISBUF+2
0025 000c ce 40 40           [ 3 ] 	LDX	#$4040		"--"
0026 000f ff e4 21           [ 6 ] 	STX	DISBUF+4	STORE THE LAST 2 DISPLAY
0027 0012 ce f0 a2           [ 3 ] 	LDX	#DIDDLE		ADDR OF DIDDLE ROUTINE
0028 0015 ff e4 19           [ 6 ] 	STX	MNPTR		ESTABLISH AS ACTIVE SUB OF PUT
0029 0018 7e f0 bb           [ 3 ] 	JMP	PUT		CALL DISPLAY ROUTINE

BEG        0000
DIDDLE     f0a2
DISBUF     e41d
MNPTR      e419
PUT        f0bb

BEG        0000 *0021 
DIDDLE     f0a2 *0015 0027 
DISBUF     e41d *0016 0022 0024 0026 
MNPTR      e419 *0017 0028 
PUT        f0bb *0018 0029 
```
