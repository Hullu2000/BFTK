BFTK (BrainFuck To Kernel) version 1.0

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
It ca be installed with the "make install" command and
uninstalled with the "make uninstall" command.

USSAGE

bftk /path/to/brainfuc/program

This will produce a file called bfos.bin. This is a kernel
that can be booted on any i686 (Pentium Pro) or newer system.
Boot loader not included. Use GRUB. You can also boot it in
Qemu with the command "qemu-system-x86_68 -kernel bfos.bin"
