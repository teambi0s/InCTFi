obj-m += MultiStorage.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL_PATH := ./linux-5.8.1/
all: exp.c
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
	gcc exp.c -o exp --static -lpthread
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	rm exp
