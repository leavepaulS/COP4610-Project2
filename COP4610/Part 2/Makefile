obj-m := my_timer.o

KERNELDIR := /lib/modules/4.15.0-45-generic/build

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o Module* *mod*