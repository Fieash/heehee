ldflags-y += -T$(src)/khook/engine.lds

obj-m += test2.o
# test2-y += test2.o

all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

