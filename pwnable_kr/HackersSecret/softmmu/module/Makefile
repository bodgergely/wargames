obj-m := softmmu.o
#softmmu-objs := softmmu.o

#KERNEL_HEADERS_LIB=/lib/modules/$(shell uname -r)/build
KERNEL_HEADERS_LIB=~/busybox/build/linux-3.7.1
#KERNEL_HEADERS_LIB=~/linux/3.7.1/linux-3.7.1


all:
	make $(MAKE_FLAG) -C $(KERNEL_HEADERS_LIB) M=$(PWD) modules

clean:
	make -C $(KERNEL_HEADERS_LIB) M=$(PWD) clean
