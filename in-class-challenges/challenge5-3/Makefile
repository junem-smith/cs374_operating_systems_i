TARGETS=fcntl_locking

.PHONY: all clean

all: $(TARGETS)

fcntl_locking: fcntl_locking.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
