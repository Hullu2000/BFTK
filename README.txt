BFTK (BrainFuck To Kernel) version 1.1

BFTK is a Perl script that turns Brainfuck into assembly and
links it with a few C files to create a working kernel that
can be booted with GRUB or Qemu. Currently BFTK requires
Perl to run and i686-elf-gcc and Nasm to work. You should be
able to find them in the package repository of your distro.

BFTK is free software released under the MIT license.
The C files are based on a few tutorials online. Mainly in
osdev.org. If I have used some of your code there that you
haven't released as public domain (as everything on osdev.org
should have been since 2011) please contact me and I'll fix
the licensing. But to be honest, why did you even put code in
a tutorial if you didn't want it to be used.

INSTALLATION

BFTK doesn't need to be compiled since it's just a script.
It can be installed with the "make install" command and
uninstalled with the "make uninstall" command.

USAGE

bftk /path/to/brainfuck/program [BG colour] [FG colour]

This will produce a file called bfos.bin. This is a kernel
that can be booted on any i686 (Pentium Pro) or newer system.
Boot loader not included. Use GRUB. You can also boot it in
Qemu with the command "qemu-system-x86_68 -kernel bfos.bin"

To input colours use numbers:

BLACK = 0
BLUE = 1
GREEN = 2
CYAN = 3
RED = 4
MAGENTA = 5
BROWN = 6
LIGHT_GREY = 7
DARK_GREY = 8
LIGHT_BLUE = 9
LIGHT_GREEN = 10
LIGHT_CYAN = 11
LIGHT_RED = 12
LIGHT_MAGENTA = 13
LIGHT_BROWN = 14
WHITE = 15
