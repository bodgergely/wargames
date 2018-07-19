
## Challange

Download: [custom softmmu kernel code](http://pwnable.kr/bin/softmmu)

`ssh softmmu@pwnable.kr -p2222 (pw:flag of syscall)`

The password is the flag contents we obtained by solving the syscall challange.


## Writeup

### Flag file

$ /tmp/m $ ls -lha /flag
-r--------    1 0        0             51 Jul  1  2014 /flag

### Kernel:

softmmu code is part of this custom kernel.

*version:* 3.7.1 - x86 - i386 

Notice: NX (Execute Disable) protection missing in CPU!
Linux version 3.7.1 (root@ubuntu) (gcc version 4.7.3 (Ubuntu/Linaro 4.7.3-1ubuntu1
) ) #1 SMP Mon Dec 23 06:07:19 PST 2013


[    0.000000 ] Kernel command line: root=/dev/ram rw console=ttyS0 rdinit=/bin/ash

$ `dmesg | grep x86`
    0.000000 ]   Transmeta GenuineTMx86
    4.081067 ] [+] Loading x86 PAE MMU emulator



$ `dmesg | grep softmmu`
    4.083557 ] [+] Write the virtual address to /proc/softmmu
    4.084989 ] [+] You can obtain it's physical address by reading /proc/softmmu
    4.086563 ] [+] i.e. echo -ne '\x00\x80\x04\x08' > /proc/softmmu; hexdump -C /proc/softmmu


[    0.000000 ] 0MB HIGHMEM available.
[    0.000000 ] 63MB LOWMEM available.
[    0.000000 ]   mapped low ram: 0 - 03fe0000
[    0.000000 ]   low ram: 0 - 03fe0000
[    0.000000 ] Zone ranges:
[    0.000000 ]   DMA      [mem 0x00010000-0x00ffffff]
[    0.000000 ]   Normal   [mem 0x01000000-0x03fdffff]
[    0.000000 ]   HighMem  empty
[    0.000000 ] Movable zone start for each node
[    0.000000 ] Early memory node ranges
[    0.000000 ]   node   0: [mem 0x00010000-0x0009efff]
[    0.000000 ]   node   0: [mem 0x00100000-0x03fdffff]
[    0.000000 ] On node 0 totalpages: 16239
[    0.000000 ] free_area_init_node: node 0, pgdat c18d2280, node_mem_map c3b5f200
[    0.000000 ]   DMA zone: 32 pages used for memmap
[    0.000000 ]   DMA zone: 0 pages reserved
[    0.000000 ]   DMA zone: 3951 pages, LIFO batch:0
[    0.000000 ]   Normal zone: 96 pages used for memmap
[    0.000000 ]   Normal zone: 12160 pages, LIFO batch:1


### Memory layout (kernel)

[    0.000000 ] virtual kernel memory layout:
[    0.000000 ]     fixmap  : 0xfff15000 - 0xfffff000   ( 936 kB )
[    0.000000 ]     pkmap   : 0xffc00000 - 0xffe00000   (2048 kB)
[    0.000000 ]     vmalloc : 0xc47e0000 - 0xffbfe000   ( 948 MB )
[    0.000000 ]     lowmem  : 0xc0000000 - 0xc3fe0000   (  63 MB )
[    0.000000 ]       .init : 0xc18e1000 - 0xc19a4000   ( 780 kB )
[    0.000000 ]       .data : 0xc15f71a6 - 0xc18e0700   (2981 kB)
[    0.000000 ]       .text : 0xc1000000 - 0xc15f71a6   (6108 kB)


### Security

[    0.029731 ] Security Framework initialized
[    0.033939 ] AppArmor: AppArmor initialized
[    0.522009] EVM: security.selinux
[    0.523125] EVM: security.SMACK64
[    0.524027] EVM: security.capability
[    0.035003] Yama: becoming mindful.
[    1.966923] AppArmor: AppArmor Filesystem Enabled
[    3.867916] Write protecting the kernel text: 6112k
[    3.869292] Write protecting the kernel read-only data: 2456k

Yama is a Linux Security Module (./security/yama/yama_lsm.c)

### CPUs

[    0.000000 ] tsc: Detected 2792.991 MHz processor
[    0.488000 ] Brought up 1 CPUs
[    0.488128 ] smpboot: Total of 1 processors activated (5585.98 BogoMIPS)
[    0.493585 ] NMI watchdog: disabled (cpu0): hardware events not enabled


### softmmu module related

[    4.073858 ] Disabling lock debugging due to kernel taint

[    4.081067 ] [+] Loading x86 PAE MMU emulator
[    4.083557 ] [+] Write the virtual address to /proc/softmmu
[    4.084989 ] [+] You can obtain it's physical address by reading /proc/softmmu
[    4.086563 ] [+] i.e. echo -ne '\x00\x80\x04\x08' > /proc/softmmu; hexdump -C /proc/softmmu
[    4.088329 ] [+] Let the kernel exploit begin :)


### Loaded modules


$ `lsmod`

  softmmu 12608 0 - Live 0xc480f000 (OF)


## softmmu module


Looks like a **virtual -> physical** address translator.


## Compile 3.7.1 kernel

The Makefile of the kernel needs patching due to PIC enabled by default on gcc 6+

https://askubuntu.com/questions/851433/kernel-doesnt-support-pic-mode-for-compiling
https://lists.ubuntu.com/archives/kernel-team/2016-May/077178.html

+KBUILD_CFLAGS += $(call cc-option, -fno-pie)
+KBUILD_CFLAGS += $(call cc-option, -no-pie)
+KBUILD_AFLAGS += $(call cc-option, -fno-pie)
+KBUILD_CPPFLAGS += $(call cc-option, -fno-pie)

















