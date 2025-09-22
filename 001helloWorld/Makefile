obj-m := main.o

KERN_VERSION := $(shell uname -r)
PWD := $(shell pwd)

all:
	$(MAKE) -C /lib/modules/$(KERN_VERSION)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(KERN_VERSION)/build M=$(PWD) clean

