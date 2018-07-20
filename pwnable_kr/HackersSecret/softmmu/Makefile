obj-m := soft.o softmmu.o_shipped

MAKE_FLAG="--debug=v"

all:
	make $(MAKE_FLAG) -C ~/busybox/build/linux-3.7.1 M=$(PWD) modules

clean:
	make -C ~/busybox/build/linux-3.7.1 M=$(PWD) clean
