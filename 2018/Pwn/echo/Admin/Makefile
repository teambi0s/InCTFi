ifndef MACHINE
  MACHINE=$(shell $(CC) -dumpmachine)
endif

ifneq (,$(findstring x86,$(MACHINE)))
   CC:=arm-linux-gnueabihf-gcc
else
   CC:=gcc
endif

all:
	$(CC)  -no-pie -Wl,-z,relro,-z,now  -fstack-protector-all  echo.c -o echo

