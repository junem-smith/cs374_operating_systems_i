TARGETS=mmap_flat_lock

.PHONY: all clean

all: $(TARGETS)

mmap_flat_lock: mmap_flat_lock.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
