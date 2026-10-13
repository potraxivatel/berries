all:
	$(MAKE) -C kernel

clean:
	$(MAKE) -C kernel clean

run: all
	qemu-system-i386 -kernel kernel/berries-kernel

.PHONY: all clean run
