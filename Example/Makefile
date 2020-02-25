obj-m := hello.o

KERNELDIR := /lib/modules/4.15.0-45-generic/build

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean