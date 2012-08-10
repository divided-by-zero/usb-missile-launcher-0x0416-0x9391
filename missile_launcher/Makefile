ifneq ($(KERNELRELEASE),)
obj-m := missile_launcher.o
else
KDIR := /usr/src/linux-headers-3.0.0-12-generic/
all:
	$(MAKE) -C $(KDIR) M=`pwd` modules
endif

clean:
	rm -f *.ko* *.o* *.mod* Module.symvers
	rm -rf .??*
