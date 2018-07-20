obj-m := soft.o softmmu.o_shipped

MAKE_FLAG="--debug=v"

all:
	make $(MAKE_FLAG) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
