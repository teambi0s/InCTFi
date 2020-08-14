# Comment/uncomment the following line to disable/enable debugging
# DEBUG = y
# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
DEBFLAGS = -O -g -DKDEBUG # "-O" is needed to expand inlines
else
DEBFLAGS = -O2
endif
EXTRA_CFLAGS += $(DEBFLAGS)

ifneq (${KERNELRELEASE},)
obj-m += mod.o
# Assignment module here
else
KERNEL_SOURCE := ../../linux_source/linux-4.9.231/
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=${PWD} modules
clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=${PWD} clean
endif
