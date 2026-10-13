all:
	$(MAKE) -C kernel

clean:
	$(MAKE) -C kernel clean

run: all
	qemu-system-x86_64 -kernel kernel/berries-kernel

.PHONY: all clean run
