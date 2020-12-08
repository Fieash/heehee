MODNAME		?= test4-demo

obj-m		+= $(MODNAME).o
$(MODNAME)-y	+= test4.o

ccflags-y	+= -Werror -fno-stack-protector -fomit-frame-pointer
ldflags-y	+= -T$(src)/khook/engine.lds

LDFLAGS		:= $(ldflags-y) # legacy
KBUILD_CFLAGS	:= $(filter-out -pg,$(KBUILD_CFLAGS))
KBUILD_CFLAGS	:= $(filter-out -mfentry,$(KBUILD_CFLAGS))