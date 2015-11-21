# Simple-Kernel
This is a simple kernel for people to build off of.
If you'd wish to contribute to the project please just email me @ znet12345678@gmail.com
If you'd like to clone this project and make modifications to it and publish it somewhere else that is 100% okay. A little bit of credit would be nice,but it's optional.
To build this project just type make. You need the i386-elf toolchain to build and nasm assembler.
Thank You for your time. I will hopefully expand on this project in the future and make this into a full kernel with I/O and mounting.
Bye
To boot the kernel with qemu use:<br> qemu-system-{i386 or x86_64} -kernel simp.kernel<br>
To boot the kernel with grub2 copy the kernel to / and the config is<br>
menuconfig "Simple-Kernel"{<br>
  set root='(hdX,Y)'<br>
  multiboot /simp.kernel<br>
}
